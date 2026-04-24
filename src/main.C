#include <string>
#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>
#include <vector>
#include "crow.h"
#include "../include/Activity.h"
#include "../include/ActivityList.h"

int port;
ActivityList All; // initialize the list from files
int main()
{ 
    std::cout<<"port: "<<std::endl;
    std::cin>>port;
    
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]() {
        crow::response res;
        res.set_static_file_info("../res/stumain.html");
        return res;
    });
    
    CROW_ROUTE(app, "/get").methods("POST"_method)([](const crow::request& req) {
        crow::response res;
        res.code = 200;
        res.set_header("Content-Type", "application/text");
        res.body = R"({'status':'success', 'content':'" + All.toString() + "'})";
        return res;
    });
    
    CROW_ROUTE(app, "/new").methods("POST"_method)([](const crow::request& req) {
        crow::response res;

        try {
            auto body = nlohmann::json::parse(req.body);
            Activity* newone = new Activity(body);
            if (!newone->save()) {
                res.code = 500;
                res.body = R"({"status":"error"})";
                return res;
            }
            All.add(newone);    
            res.code = 200;
            res.set_header("Content-Type", "application/json");
            res.body = R"({"status":"success"})";
            return res;
        } catch (...) {
            res.code = 400;
            res.body = R"({"status":"invalid json"})";
            return res;
        }
    });

    app.port(18080).multithreaded().run();
}


