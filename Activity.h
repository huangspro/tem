#ifndef _ACTIVITY_H_
#define _ACTIVITY_H_

#include <string>
#include <fstream>

class Activity {
private:
    std::string start_time, end_time, checkin_time, checkout_time; // Y-M-D-H-M-S
    std::string position, checkin_position, checkout_position;
    std::string title, introduction, detail;
    std::string participant_number, participant_condition, reward;
    std::string signup_url, checkin_url, checkout_url;

    int id;

public:
    Activity(
        int id = 0,
        std::string title = "",
        std::string introduction = "",
        std::string detail = "",
        std::string start_time = "",
        std::string end_time = "",
        std::string position = "",
        std::string participant_number = "",
        std::string participant_condition = "",
        std::string reward = "",
        std::string signup_url = "",
        std::string checkin_url = "",
        std::string checkout_url = ""
    )
    : start_time(start_time),
      end_time(end_time),
      checkin_time(""),
      checkout_time(""),
      position(position),
      checkin_position(""),
      checkout_position(""),
      title(title),
      introduction(introduction),
      detail(detail),
      participant_number(participant_number),
      participant_condition(participant_condition),
      reward(reward),
      signup_url(signup_url),
      checkin_url(checkin_url),
      checkout_url(checkout_url),
      id(id)
    {}

    // 转字符串
    std::string toString() {
        return "Activity{id=" + std::to_string(id) +
               ", title=" + title +
               ", intro=" + introduction +
               ", detail=" + detail + "}";
    }

    // 保存到 txt 文件
    bool save(const std::string& filename) {
        std::ofstream out(filename);
        if (!out.is_open()) return false;

        out << toString();
        out.close();
        return true;
    }

    int getId() const {
        return id;
    }
};

#endif
