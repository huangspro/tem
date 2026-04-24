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
  
  bool add(Activity* act);
  bool del(int id);
  std::string toString();
};

#endif
