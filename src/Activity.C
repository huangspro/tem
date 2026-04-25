#include <string>
#include <fstream>
#include <sstream>
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
Activity::Activity(const nlohmann::json& j) {
        id = j.value("id", 0);
        title = j.value("title", "");
        introduction = j.value("introduction", "");
        detail = j.value("detail", "");

        start_time = j.value("start_time", "");
        end_time = j.value("end_time", "");

        position = j.value("position", "");
        checkin_position = j.value("checkin_position", "");
        checkout_position = j.value("checkout_position", "");

        checkin_time = j.value("checkin_time", "");
        checkout_time = j.value("checkout_time", "");

        participant_number = j.value("participant_number", "");
        participant_condition = j.value("participant_condition", "");
        reward = j.value("reward", "");

        signup_url = j.value("signup_url", "");
        checkin_url = j.value("checkin_url", "");
        checkout_url = j.value("checkout_url", "");
    }

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
    if (!file.is_open())return false;

    nlohmann::json j;
    try
    {
        file >> j;
    }
    catch (...)
    {
        return false; 
    }
    if (j.contains("id")) id = j["id"];
    if (j.contains("title")) title = j["title"];
    if (j.contains("introduction")) introduction = j["introduction"];
    if (j.contains("detail")) detail = j["detail"];
    if (j.contains("start_time")) start_time = j["start_time"];
    if (j.contains("end_time")) end_time = j["end_time"];
    if (j.contains("position")) position = j["position"];
    if (j.contains("participant_number")) participant_number = j["participant_number"];
    if (j.contains("participant_condition")) participant_condition = j["participant_condition"];
    if (j.contains("reward")) reward = j["reward"];
    if (j.contains("signup_url")) signup_url = j["signup_url"];
    if (j.contains("checkin_url")) checkin_url = j["checkin_url"];
    if (j.contains("checkout_url")) checkout_url = j["checkout_url"];

    return true;
}

int Activity::getId(){
    return id;
}
