#include <list>
#include <string>
#include <functional>
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "User.h"
#include "Meeting.h"
#include "Storage.h"

Storage *Storage::instance_ = NULL;

Storage::Storage() {
    userList_.clear();
    meetingList_.clear();
    readFromFile("./");
}

Storage::~Storage() {
    sync();
    instance_ = NULL;
}

bool Storage::readFromFile(const char *fpath) {
    std::string p = fpath;
    std::ifstream fu(p+"User.csv");
    userList_.clear();
    meetingList_.clear();
    if (!fu) {
        // std::cerr << "The file could not read" << std::endl;
        return false;
    } else {
        std::string u1;
        while (getline(fu, u1)) {
            int i1, i2, i3, i4;
            const char* a = "\",\"";
            std::string name, password, email, phone;
            i1 = u1.find(a, 0);
            name = u1.substr(1, i1-1);
            i2 = u1.find(a, i1+2);
            password = u1.substr(i1+3, i2-i1-3);
            i3 = u1.find(a, i2+2);
            email = u1.substr(i2+3, i3-i2-3);
            i4 = u1.find("\"", i3+3);
            phone = u1.substr(i3+3, i4-i3-3);
            if (name != "name") {
            User user(name, password, email, phone);
            userList_.push_back(user);
            }
            name.clear();
            password.clear();
            email.clear();
            phone.clear();
        }
    fu.close();
    std::ifstream fm(p+"Meeting.csv");
    if (!fm) {
        return false;
    } else {
        std::string u1;
        while (getline(fm, u1)) {
            int i1, i2, i3, i4, i5;
            const char* a = "\",\"";
            std::string sponsor, participator, sdate, edate, title;
            i1 = u1.find(a, 0);
            sponsor = u1.substr(1, i1-1);
            i2 = u1.find(a, i1+1);
            participator = u1.substr(i1+3, i2-i1-3);
            i3 = u1.find(a, i2+1);
            sdate= u1.substr(i2+3, i3-i2-3);
            i4 = u1.find(a, i3+1);
            edate = u1.substr(i3+3, i4-i3-3);
            i5 = u1.find("\"", i4+3);
            title = u1.substr(i4+3, i5-i4-3);
            if (sponsor != "sponsor") {
            Meeting meeting(sponsor, participator, Date::stringToDate(sdate), 
            Date::stringToDate(edate), title);
            meetingList_.push_back(meeting);
            }
            sponsor.clear();
            participator.clear();
            sdate.clear();
            edate.clear();
            title.clear();
        }
        fm.close();
        }
    }
    return true;
}

bool Storage::writeToFile(const char *fpath) {
    std::ofstream fu, fm;
    std::string p = fpath;
    fu.open(p + "User.csv");
    if (! fu) {
        return false;
    } else {
        fu << "\"name\",\"password\",\"email\",\"phone\"" << std::endl;
        std::list<User>::iterator it;
        for (it = userList_.begin(); it != userList_.end(); it++) {
            fu << "\"" << it->getName() << "\",\"" << it->getPassword() << "\",\"" 
            << it->getEmail() << "\",\"" << it->getPhone() << "\"" << std::endl;
        }
    }
    
    fu.close();
    fm.open(p + "Meeting.csv");
    if (! fm) {
        return false;
    } else {
        fm << "\"sponsor\",\"paticipator\",\"sdate\",\"edate\",\"title\"" << std::endl;
        std::list<Meeting>::iterator t;
        for (t = meetingList_.begin(); t != meetingList_.end(); t++) {
            fm << "\"" << t->getSponsor() << "\",\"" << t->getParticipator()
                        << "\",\"" << Date::dateToString(t->getStartDate()) 
                        << "\",\"" << Date::dateToString(t->getEndDate())
            << "\",\"" << t->getTitle() << "\"" << std::endl;
        }
    }
    
    fm.close();
    return true;
    
}

Storage *Storage::getInstance(void) { // static
    if (instance_ == NULL) {
        instance_ = new Storage;
    }
    return instance_;
}


void Storage::createUser(const User& u) {
    userList_.push_back(u);
}

std::list<User> Storage::queryUser(std::function<bool(const User&)> filter) { // return found users
    std::list<User> temp;
    std::list<User>::iterator u;
    for (u = userList_.begin(); u != userList_.end(); u++) {
        if (filter(*u)) temp.push_back(*u);
    }
    return temp;
}

int Storage::updateUser(std::function<bool(const User&)> filter,
                         std::function<void(User&)> switcher) {    // return the number of updated users
                         int total = 0;
                         std::list<User>::iterator u;
                         for (u = userList_.begin(); u != userList_.end(); u++) {
                             if (filter(*u)) {
                                 switcher(*u);
                                 total++;
                             }
                         }
                         return total;
                     }

int Storage::deleteUser(std::function<bool(const User&)> filter) { // return the number of deleted users
    int total = 0;
    std::list<User>::iterator u;
    for (u = userList_.begin(); u != userList_.end();) {
        if (filter(*u)) {
            u = userList_.erase(u);
            total++;
        } else {
            u++;
        }
    }
    return total;
}
    
void Storage::createMeeting(const Meeting& m) {
    meetingList_.push_back(m);
}
std::list<Meeting> Storage::queryMeeting(std::function<bool(const Meeting&)> filter) { // return found meetings
    std::list<Meeting> temp;
    std::list<Meeting>::iterator m;
    for (m = meetingList_.begin(); m != meetingList_.end(); m++) {
        if (filter(*m)) temp.push_back(*m);
    }
    return temp;
}
                     
   
int Storage::updateMeeting(std::function<bool(const Meeting&)> filter,
                              std::function<void(Meeting&)> switcher) { // return the number of updated meetings
                              int total = 0;
                              std::list<Meeting>::iterator m;
                              for (m = meetingList_.begin(); m != meetingList_.end(); m++) {
                              if (filter(*m)) {
                                  switcher(*m);
                                  total++;
                                 }
                             }
                             return total;
                         }
   
int Storage::deleteMeeting(std::function<bool(const Meeting&)> filter) {    // return the number of deleted meetings
    int total = 0;
    std::list<Meeting>::iterator m;
    for (m = meetingList_.begin(); m != meetingList_.end();) {
        if (filter(*m)) {
            m = meetingList_.erase(m);
            total++;
        } else {
            m++;
        }
    }
    return total;
}

    
bool Storage::sync(void) {// File IO
    return writeToFile("./");
}
