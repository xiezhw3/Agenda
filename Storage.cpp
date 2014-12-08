#include "Storage.h"
#include "Json.h"
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <vector>

Storage *Storage::instance_ = nullptr;

Storage::Storage() {
    if (readFromFile("agenda.data") == false) {
        userList_.clear();
        meetingList_.clear();
    }
}

Storage* Storage::getInstance(void) {
    if (!instance_) {
        instance_ = new Storage();
    }
    return instance_;
}

Storage::~Storage() {
    writeToFile("agenda.data");
}

bool Storage::sync(void) {
    return writeToFile("agenda.data");
}

void Storage::createUser(const User& user_) {
    userList_.push_back(user_);
}

std::list<User> Storage::queryUser(std::function<bool(const User&)> filter) {
    std::list<User> v;
    for (auto i : userList_) {
        if (filter(i))
            v.push_back(i);
    }
    return v;
}

int Storage::updateUser(std::function<bool(const User&)> filter, std::function<void(User&)> switcher) {
    int result = 0;
    for (auto i : userList_) {
        if (filter(i)) {
            switcher(i);
            result++;
        }
    }
    return result;
}

int Storage::deleteUser(std::function<bool(const User&)> filter) {
    int result = 0;
    for (auto i = userList_.begin(); i != userList_.end(); ) {
        if (filter(*i)) {
            i = userList_.erase(i);
            result++;
        } else {
            ++i;
        }
    }
    return result;
}

void Storage::createMeeting(const Meeting& meeting_) {
    meetingList_.push_back(meeting_);
}

std::list<Meeting> Storage::queryMeeting(std::function<bool(const Meeting&)> filter) {
    std::list<Meeting> v;
    for (auto i : meetingList_) {
        if (filter(i))
            v.push_back(i);
    }
    return v;
}

int Storage::updateMeeting(std::function<bool(const Meeting&)> filter, std::function<void(Meeting&)> switcher) {
    int result = 0;
    for (auto i : meetingList_) {
        if (filter(i)) {
            switcher(i);
            result++;
        }
    }
    return result;
}

int Storage::deleteMeeting(std::function<bool(const Meeting&)> filter) {
    int result = 0;
    for (auto i = meetingList_.begin(); i != meetingList_.end();) {
        if (filter(*i)) {
            i = meetingList_.erase(i);
            result++;
        } else {
            ++i;
        }
    }
    return result;
}

//-----------------------first----------------------------------------------
// bool Storage::ReadFromFile(char* fpath) {
//   std::ifstream in;
//   in.open(fpath);
//   if (!in.is_open())
//     return false;
//   std::string userNum_pattern = ("{collection:\"User\",total:(\\d+)}")
//   std::string strtmp;
//   std::getline(in, strtmp, '\n');

//   std::string numSet = "0123456789";
//   int first = strtmp.find_first_of(numSet);
//   int last = strtmp.find_last_of(numSet);
//   if (first == std::string::npos || last == std::string::npos) {
//     return false;
//   }
//   std::string numOfUserStr = strtmp.substr(first, last - first + 1);
//   std::stringstream ss(numOfUserStr);

//   int numOfUser;
//   ss >> numOfUser;

//   std::string nameStr, pwdStr, phoneStr;
//   for (int i = 0; i < numOfUser; i++) {
//     std::getline(in, strtmp, '\n');
//     first = strtmp.find_first_of(",");
//     last = strtmp.find_last_of(",");

//     nameStr = strtmp.substr(0, first);
//     pwdStr = strtmp.substr(first + 1, last);
//     phoneStr = strtmp.substr(last + 1);

//     nameStr = nameStr.substr(nameStr.find(":"));
//     pwdStr = pwdStr.substr(pwdStr.find(":"));
//     phoneStr = phoneStr.substr(phoneStr.find(":"));
//     phoneStr = phoneStr.substr(0, phoneStr.find("}"));

//     User user = new User(nameStr, pwdStr, phoneStr);
//     userList_.push_back(user);
//   }

//   std::getline(in, strtmp, '\n');
//   int first = strtmp.find_first_of(numSet);
//   int last = strtmp.find_last_of(numSet);

//   ss << (strtmp.substr(first, last - first + 1));
//   int numOfMeeting;
//   ss >> numOfMeeting;
//   for (int i = 0; i != numOfMeeting; i++) {
//     std::getline(in, strtmp, '\n');
//     std::size_t found = strtmp.find_first_of(",");
//     std::vector<std::size_t> foundList;
//     while (found != std::string::nops) {
//       foundList.push_back(found);
//       found = str.find_first_of(",", found + 1);
//     }

//     std::string sponsor = strtmp.substr(0, foundList[0]);
//     std::string participator = strtmp:substr(foundList[0] + 1, foundList[1]);
//     std::string st_date = strtmp.substr(foundList[1] + 1, foundList[2]);
//     std::string ed_date = strcmp.substr(foundList[2] + 1, foundList[3]);
//     std::string title = strcmp.substr(foundList[3]);

//     sponsor = sponsor.substr(sponsor.find(":"));
//     participator = participator.substr(participator.find(":"));
//     st_date = st_date.substr(st_date.find(":"));
//     ed_date = ed_date.substr(ed_date.find(":"));
//     ed_date = ed_date.substr(0, ed_date.find("}"));

//     Meeting meeting = new Meeting(sponsor, participator, Date::stringToDate(st_date),
//                                   Date::stringToDate(ed_date), title);
//     meetingList.push_back(meeting);
//   }

//   return true;
// }

//-----------------------second----------------------------------------------
//bool Storage::readFromFile(const char* fpath) {
//    std::ifstream in;
//    in.open("agenda.data", std::ifstream::in);
//    if (!in.is_open())
//        return false;
//    
//    std::string numOfRecode;
//    std::getline(in, numOfRecode);
//    if (numOfRecode.size() == 0)
//        return true;
//    
//    std::match_results<std::string::const_iterator> result;
//    std::regex reg( "\\d+" );
//    regex_search(numOfRecode, result, reg);
//    std::stringstream ss(result[0]);
//    int recordNum;
//    ss >> recordNum;
//    std::regex reg2( "(\\w+):\"(.+)\",(\\w+):\"(.+)\",(\\w+):\"(.+)\",(\\w+):\"(\\d+)\"}" );
//    for (int i = 0; i != recordNum; i++) {
//        std::getline(in, numOfRecode);
//        regex_search(numOfRecode, result, reg2);
//        User user(result[2], result[4], result[6], result[8]);
//        userList_.push_back(user);
//    }
//    
//    std::getline(in, numOfRecode);
//    if (numOfRecode.size() == 0)
//        return true;
//    
//    regex_search(numOfRecode, result, reg);
//    std::stringstream ss2(result[0].str());
//    ss2 >> recordNum;
//    std::regex reg3( "(\\w+):\"(.+)\",(\\w+):\"(.+)\",(.+):\"(.+)\",(.+):\"(.+),(\\w+):\"(.+)\"}" );
//    for (int i = 0; i != recordNum; i++) {
//        std::getline(in, numOfRecode);
//        regex_search(numOfRecode, result, reg3);
//        Meeting meeting(result[2], result[4], Date::stringToDate(result[6]), Date::stringToDate(result[8]), result[10]);
//        meetingList_.push_back(meeting);
//    }
//    
//    in.close();
//    return true;
//}




bool Storage::readFromFile(const char* fpath) {
    std::ifstream in;
    in.open("agenda.data", std::ifstream::in);
    if (!in.is_open())
        return false;
    Json json;
    int Recordnum;
    std::string numOfRecode;
    std::getline(in, numOfRecode);
    Recordnum = json.splitNum(numOfRecode);
    std::vector<std::string> record;
    
    for (int i = 0; i != Recordnum; i++) {
        std::getline(in, numOfRecode);
        record = json.splitRecordList(numOfRecode);
        User user(record[0], record[1], record[2], record[3]);
        userList_.push_back(user);
    }
    
    std::getline(in, numOfRecode);
    Recordnum = json.splitNum(numOfRecode);
    record.clear();
    
    for (int i = 0; i != Recordnum; i++) {
        std::getline(in, numOfRecode);
        record = json.splitRecordList(numOfRecode);
        Meeting meeting(record[0], record[1], Date::stringToDate(record[2]), Date::stringToDate(record[3]), record[4]);
        meetingList_.push_back(meeting);
    }
    
    in.close();
    return true;
}

bool Storage::writeToFile(const char* fpath) {
    std::ofstream out;
    out.open(fpath);
    if (!out.is_open())
        return false;
    
    std::string userWrite = "{collection:\"User\",total:";
    std::string userWriteTmp = "";
    int i = 0;
    for (auto iter = userList_.begin(); iter != userList_.end(); iter++) {
        userWriteTmp += ("{name:\"" + iter->getName() + \
                         "\",password:\"" + iter->getPassword() + \
                         "\",email:\"" + iter->getEmail() + \
                         "\",phone:\"" + iter->getPhone() + "\"}\n");
        i++;
    }
    
    char numOfRecode[20];
    sprintf(numOfRecode, "%d", i);
    userWrite += (std::string(numOfRecode) + "}\n" + userWriteTmp);
    
    std::string meetingWrite = "{collection:\"Meeting\",total:";
    std::string meetingWriteTmp = "";
    i = 0;
    for (auto iter = meetingList_.begin(); iter != meetingList_.end(); iter++) {
        meetingWriteTmp += ("{sponsor:\"" + iter->getSponsor() + \
                            "\",participator:\"" + iter->getParticipator() + \
                            "\",sdate:\"" + Date::dateToString(iter->getStartDate()) + \
                            "\",edate:\"" + Date::dateToString(iter->getEndDate()) + \
                            "\",title:\"" + iter->getTitle() + "\"}\n");
        i++;
    }
    sprintf(numOfRecode, "%d", i);
    meetingWrite += (std::string(numOfRecode) + "}\n" + meetingWriteTmp);
    out << userWrite << meetingWrite;
    out.close();
    return true;
}
