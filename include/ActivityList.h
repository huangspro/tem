#ifndef _ACTIVITYLIST_H_
#define _ACTIVITYLIST_H_

#include<string>
#include<vector>

#include "Activity.h"

class ActivityList{
private:
  int act_number, state;
  std::vector<Activity*> list;
public:
  ActivityList(std::vector<Activity*> act):list(act), act_number(act.size()){}
  ActivityList();  //In this condition, we intialize the list from ../activities/
  bool add(Activity* act);
  bool del(int id);
  std::string toString();
  bool save();    //save a series of files list from ../activities/
  bool read();   //read files from ../activities/
  Activity* find(int id);
  bool remove(int id);
};

#endif
