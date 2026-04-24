#include <string>
#include <fstream>
#include <sstream>

std::string Activity::toString()
{
    std::ostringstream oss;

    oss << "Title: " << title << "\n"
        << "Introduction: " << introduction << "\n"
        << "Detail: " << detail << "\n"
        << "Start Time: " << start_time << "\n"
        << "End Time: " << end_time << "\n"
        << "Position: " << position << "\n"
        << "Participant Number: " << participant_number << "\n"
        << "Participant Condition: " << participant_condition << "\n"
        << "Reward: " << reward << "\n"
        << "Signup URL: " << signup_url << "\n"
        << "Checkin URL: " << checkin_url << "\n"
        << "Checkout URL: " << checkout_url << "\n"
        << "id: " << id.toString() << "\n";

    return oss.str();
}


// Save activity data to text file
bool Activity::save(const std::string& filename)
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        return false;
    }

    file << toString();
    return true; // ofstream 会自动关闭（RAII）
}
