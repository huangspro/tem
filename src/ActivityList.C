#include "../include/ActivityList.h"

ActivityList::ActivityList()
{
    std::string dir = "../activities/";
    if (!fs::exists(dir) || !fs::is_directory(dir))
    {
        return; 
    }

    for (const auto& entry : fs::directory_iterator(dir))
    {
        if (!entry.is_regular_file()) continue；
        fs::path path = entry.path();
        if (path.extension() != ".act") continue;
        
        std::string name = path.stem().string();
        int id = std::stoi(name);
        Activity* newone = new Activity();
        if (newone->read(id))activitylist.add(&activity);
    }
}

bool ActivityList::add(Activity* act){
  for(int i=0;i<list.size();i++){
    if(i==act)return false;
  }
  list.push_back(act);
  return true;
}

bool del(int id){
  for(int i=0;i<list.size();i++){
    if(i->getId() == id)list.erase(list.begin() + i);
    return true;
  }
  return false;
}

//return a string containing the json string
std::string ActivityList::toString(){
  std::string result = "[";
  for(int i=0;i<list.size();i++){
    result += i->toString();
    if(i!=list.size()-1)result += ",";
  }
  result += "]"
  return result;
}

bool save(){
  for(int i=0;i<list.size();i++){
    if(!list[i]->save())return false;
  }
  return true;
}

// read data from files to update the list
bool read(){
  for(int i=0;i<list.size();i++){
    if(!list[i]->read(list[i]->getId()))return false;
  }
  return true;
}
