#include <string>
#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>
#include <vector>
#include "crow.h"
#include "../include/Activity.h"
#include "../include/ActivityList.h"
#include "../res/main.h"
#include "../res/create.h"

int port;
ActivityList All;
int main()
{ 
    std::cout<<"port: "<<std::endl;
    std::cin>>port;
    
    crow::SimpleApp app;

    // main page
    CROW_ROUTE(app, "/main")([]() {
        return mainPage;
    });
    
    // main page
    CROW_ROUTE(app, "/create")([]() {
        return createPage;
    });
    
    // api to get all the activities
    CROW_ROUTE(app, "/get").methods("POST"_method)([](const crow::request& req) {
        crow::response res;
        std::cout<<All.toString()<<std::endl;
        res.code = 200;
        res.set_header("Content-Type", "application/text");
        res.body = R"({'status':'success', 'content':'" + All.toString() + "'})";
        return res;
    });
    
    // api to create an activity and save one the server
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


