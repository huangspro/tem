#include <string>
#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>

#include "crow.h"
#include "ActivityList.h"

int port;

int main()
{ 
    std::cout<<"port: "<<std::endl;
    std::cin>>port;
    
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]() {
        crow::response res;
        res.set_static_file_info("stumain.html");
        return res;
    });
    
    CROW_ROUTE(app, "/get").methods("POST"_method)([](const crow::request& req) {
        crow::response res;
        res.code = 200;
        res.set_header("Content-Type", "application/text");
        res.body = R"({"status":"success","msg":"File uploaded successfully"})";
        return res;
    });

    app.port(18080).multithreaded().run();
}


