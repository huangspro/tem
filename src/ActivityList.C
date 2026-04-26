#include <nlohmann/json.hpp>
#include "../include/ActivityList.h"
#include <filesystem>
#include<iostream>
#include <string>

namespace fs = std::filesystem;

// Constructor: loads all .act files from the activities directory and initializes the activity list
ActivityList::ActivityList()
{
    std::string dir = "../activities/";
    if (!fs::exists(dir) || !fs::is_directory(dir))
    {
        return;
    }

    for (const auto& entry : fs::directory_iterator(dir))
    {
        if (!entry.is_regular_file()) continue;

        fs::path path = entry.path();
        if (path.extension() != ".act") continue;

        std::string name = path.stem().string();
        int id = std::stoi(name);

        Activity* newone = new Activity("","","","","","","","","","","","","","","","");

        if (newone->read(id))
        {
            add(newone);
        }
        else
        {
            delete newone;
        }
    }
}

// Adds an Activity pointer to the internal list if it is not already present
bool ActivityList::add(Activity* act)
{
    for (int i = 0; i < list.size(); i++)
    {
        if (list[i] == act)
            return false;
    }

    list.push_back(act);
    return true;
}

// Deletes an Activity from the list by its ID and frees its memory
bool ActivityList::del(int id)
{
    for (int i = 0; i < list.size(); i++)
    {
        if (list[i]->getId() == id)
        {
            delete list[i];
            list.erase(list.begin() + i);
            return true;
        }
    }
    return false;
}

// Serializes all activities in the list into a JSON-like string
std::string ActivityList::toString()
{
    std::string result = "[";

    for (int i = 0; i < list.size(); i++)
    {
        result += list[i]->toString();
        if (i != list.size() - 1)
            result += ",";
    }

    result += "]";
    return result;
}

// Saves all activities in the list to their respective storage files
bool ActivityList::save()
{
    for (int i = 0; i < list.size(); i++)
    {
        if (!list[i]->save())
            return false;
    }
    return true;
}

// Reloads all activities from persistent storage using their IDs
bool ActivityList::read()
{
    for (int i = 0; i < list.size(); i++)
    {
        if (!list[i]->read(list[i]->getId()))
            return false;
    }
    return true;
}

Activity* ActivityList::find(int id)
{
    for (auto* a : list) {
        if (a->getId() == id) {
            return a;
        }
    }
    return nullptr;
}

bool ActivityList::remove(int id)
{
    for (auto it = list.begin(); it != list.end(); ++it) {
        if ((*it)->getId() == id) {
            delete *it;          // 如果你 new 过
            list.erase(it);
            return true;
        }
    }
    return false;
}
