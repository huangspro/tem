#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <nlohmann/json.hpp>
#include<iostream>
#include "../include/Activity.h"

std::string Activity::toString()
{
    nlohmann::json j;

    j["id"] = id;
    j["title"] = title;
    j["introduction"] = introduction;
    j["detail"] = detail;
    j["start_time"] = start_time;
    j["end_time"] = end_time;
    j["position"] = position;
    j["participant_number"] = participant_number;
    j["participant_condition"] = participant_condition;
    j["reward"] = reward;
    j["signup_url"] = signup_url;
    j["checkin_url"] = checkin_url;
    j["checkout_url"] = checkout_url;

    // pretty print（更易读）
    return j.dump(4);
}

//initialize the class by json object
Activity::Activity(const nlohmann::json& j): Activity(
    j.value("title", ""),
    j.value("introduction", ""),
    j.value("detail", ""),
    j.value("start_time", ""),
    j.value("end_time", ""),
    j.value("position", ""),
    j.value("checkin_time", ""),
    j.value("checkout_time", ""),
    j.value("checkin_position", ""),
    j.value("checkout_position", ""),
    j.value("participant_number", ""),
    j.value("participant_condition", ""),
    j.value("reward", ""),
    j.value("signup_url", ""),
    j.value("checkin_url", ""),
    j.value("checkout_url", "")
)
{}

// Save activity data to text file
bool Activity::save()
{
    std::string filename = "../activities/" + std::to_string(id) + ".act";
    std::ofstream file(filename);
    if (!file.is_open())
    {
        return false;
    }

    file << toString();
    return true;
}

bool Activity::read(int ID)
{
    std::string filename = "../activities/" + std::to_string(ID) + ".act";
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    nlohmann::json j;
    try
    {
        file >> j;
    }
    catch (...)
    {
        return false;
    }
    id = j.value("id", 0);
    title = j.value("title", "");
    introduction = j.value("introduction", "");
    detail = j.value("detail", "");
    start_time = j.value("start_time", "");
    end_time = j.value("end_time", "");
    position = j.value("position", "");
    checkin_time = j.value("checkin_time", "");
    checkout_time = j.value("checkout_time", "");
    checkin_position = j.value("checkin_position", "");
    checkout_position = j.value("checkout_position", "");
    participant_number = j.value("participant_number", "");
    participant_condition = j.value("participant_condition", "");
    reward = j.value("reward", "");
    signup_url = j.value("signup_url", "");
    checkin_url = j.value("checkin_url", "");
    checkout_url = j.value("checkout_url", "");

    return true;
}

int Activity::getId(){
    return id;
}


bool Activity::del()
{
    if (id <= 0)return false;
    std::string filename = "../activities/" + std::to_string(id) + ".act";
    std::cout<<filename<<std::endl;
    if (std::remove(filename.c_str()) == 0)return true;
    else return false;
}
