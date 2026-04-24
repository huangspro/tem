#include<ActivityList>

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

std::string ActivityList::toString(){
  std::string result = "";
  for(int i=0;i<list.size();i++){
    result += "<sep>";
    result += i->toString();
  }
  return result;
}
