#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include "Date.h"

Date::Date() {
    year_ = 0;
    month_ = 0;
    day_ = 0;
    hour_ = 0;
    minute_ = 0;
}

Date::Date(int y, int m, int d, int h, int mi) {
    year_ = y;
    month_ = m;
    day_ = d;
    hour_ = h;
    minute_ = mi;
}

int Date::getYear(void) const {
    return year_;
}

void Date::setYear(int year) {
    year_ = year;
}

int Date::getMonth(void) const {
    return month_;
}

void Date::setMonth(int month) {
    month_ = month;
}

int Date::getDay(void) const {
    return day_;
}

void Date::setDay(int day) {
    day_ = day;
}

int Date::getHour(void) const {
    return hour_;
}

void Date::setHour(int hour) {
    hour_ = hour;
}

int Date::getMinute(void) const {
    return minute_;
}

void Date::setMinute(int minute) {
    minute_ = minute;
}

bool Date::isValid(Date date) {
    if (date.getYear() < 1000 || date.getYear() > 9999) return false;
    if (date.getMonth() < 1 || date.getMonth() > 12) return false;
    if (date.getMonth() == 1|| date.getMonth() == 3 || date.getMonth() == 5 
    || date.getMonth() == 7 || date.getMonth() == 8 || date.getMonth() == 10 
    || date.getMonth() == 12) {
         if (date.getDay() <= 0 || date.getDay() > 31) return false;
         } else if (date.getMonth() == 4|| date.getMonth() == 6 || 
                        date.getMonth() == 9 || date.getMonth() == 11) {
                            if (date.getDay() <= 0 || date.getDay() > 30)
                                return false;
                        } else if (date.getMonth() == 2) {
                            if ((date.getYear()%4 == 0 && date.getYear()%100 != 0) || 
                                date.getYear()%400 == 0) {
                                if (date.getDay() <= 0 || date.getDay() > 29)
                                    return false;
                            } else {
                                if (date.getDay() <= 0 || date.getDay() > 28)
                                    return false;
                            }
                        }
    if (date.getHour() < 0 || date.getHour() > 23) return false;
    if (date.getMinute() < 0 || date.getMinute() > 59) return false;
    return true;
}

Date Date::stringToDate(std::string dateString) {
    int i, i2, i3, i4;
    Date d;
    Date wrong(0, 0, 0, 0, 0);
    std::string y, m, dd, h, mm ;
    std::stringstream ss;
    
    i = dateString.find("-", 0);
    if (i == dateString.npos) return wrong;
    y = dateString.substr(0, i);
    i2 = dateString.find("-", i+1);
    if (i2 == dateString.npos) return wrong;
    m = dateString.substr(i+1, i2-i);
    i3 = dateString.find("/", i2+1);
    if (i3 == dateString.npos) return wrong;
    dd = dateString.substr(i2+1, i3-i2-1);
    i4 = dateString.find(":", i3+1);
    if (i4 == dateString.npos) return wrong;
    h = dateString.substr(i3+1, i4-i3-1);
    mm = dateString.substr(i4+1);
    ss << y;
    ss >> d.year_;
    ss.clear();
    ss << m;
    ss >> d.month_;
    ss.clear();
    ss << dd;
    ss >> d.day_;
    d.day_ = -d.day_;
    ss.clear();
    ss << h;
    ss >> d.hour_;
    ss.clear();
    ss << mm;
    ss >> d.minute_;
    return d;
}

std::string Date::dateToString(Date date) {
    std::string date1;
    std::stringstream ss;
    std::string date2;
    ss.clear();
    ss << date.getYear();
    ss >> date1;
    const char* t = "-";
    date1 += t;
    if (date.getMonth() < 10) {
        ss.clear();
        ss << date.getMonth();
        ss >> date2;
        date1 += "0" + date2;
    } else {
        std::string date2;
        ss.clear();
        ss << date.getMonth();
        ss >> date2;
        date1 += date2;
    }
    date1 += t;
    if (date.getDay() < 10) {
        ss.clear();
        ss << date.getDay();
        ss >> date2;
        date1 += "0" + date2;
    } else {
        std::string date2;
        ss.clear();
        ss << date.getDay();
        ss >> date2;
        date1 += date2;
    }
    const char* tt = "/";
    date1 += tt;
    if (date.getHour() < 10) {
        ss.clear();
        ss << date.getHour();
        ss >> date2;
        date1 += "0" + date2;
    } else {
        std::string date2;
        ss.clear();
        ss << date.getHour();
        ss >> date2;
        date1 += date2;
    }
    const char* ttt = ":";
    date1 += ttt;
    if (date.getMinute() < 10) {
        ss.clear();
        ss << date.getMinute();
        ss >> date2;
        date1 += "0" + date2;
    } else {
        ss.clear();
        ss << date.getMinute();
        ss >> date2;
        date1 += date2;
    }
    return date1;
}

Date &Date::operator=(const Date& date) {
    year_ = date.getYear();
    month_ = date.getMonth();
    day_ = date.getDay();
    hour_ = date.getHour();
    minute_ = date.getMinute();
    return *this;
}

bool Date::operator ==(const Date& date) const {
    if (year_ == date.getYear() &&
        month_ == date.getMonth() &&
        day_ == date.getDay() &&
        hour_ == date.getHour() &&
        minute_ == date.getMinute()) return true;
    else return false;
}

bool Date::operator >(const Date& date) const {
    if (year_ < date.getYear()) return false;
    else if (year_ > date.getYear()) return true;
    else if (year_ == date.getYear()){
        if (month_ < date.getMonth()) return false;
        else if (month_ > date.getMonth()) return true;
        else if (month_ == date.getMonth()) {
            if (day_ < date.getDay()) return false;
            else if (day_ > date.getDay()) return true;
            else if (day_ == date.getDay()) {
                if (hour_ < date.getHour()) return false;
                else if (hour_ > date.getHour()) return true;
                else if (hour_  == date.getHour()) {
                    if (minute_ <= date.getMinute()) return false;
                    else return true;
                }
            }
        }
    }
    return true;
}

bool Date::operator <(const Date& date) const {
    if (year_ > date.getYear()) return false;
    else if (year_ < date.getYear()) return true;
    else if (year_ == date.getYear()){
        if (month_ > date.getMonth()) return false;
        else if (month_ < date.getMonth()) return true;
        else if (month_ == date.getMonth()) {
            if (day_ > date.getDay()) return false;
            else if (day_ < date.getDay()) return true;
            else if (day_ == date.getDay()) {
                if (hour_ > date.getHour()) return false;
                else if (hour_ < date.getHour()) return true;
                else if (hour_  == date.getHour()) {
                    if (minute_ >= date.getMinute()) return false;
                    else return true;
                }
            }
        }
    }
    return true;
}

bool Date::operator >=(const Date& date) const {
    if (year_ < date.getYear()) return false;
    else if (year_ > date.getYear()) return true;
    else if (year_ == date.getYear()){
        if (month_ < date.getMonth()) return false;
        else if (month_ > date.getMonth()) return true;
        else if (month_ == date.getMonth()) {
            if (day_ < date.getDay()) return false;
            else if (day_ > date.getDay()) return true;
            else if (day_ == date.getDay()) {
                if (hour_ < date.getHour()) return false;
                else if (hour_ > date.getHour()) return true;
                else if (hour_  == date.getHour()) {
                    if (minute_ < date.getMinute()) return false;
                    else return true;
                }
            }
        }
    }
    return true;
}

bool Date::operator <=(const Date& date) const {
    if (year_ > date.getYear()) return false;
    else if (year_ < date.getYear()) return true;
    else if (year_ == date.getYear()){
        if (month_ > date.getMonth()) return false;
        else if (month_ < date.getMonth()) return true;
        else if (month_ == date.getMonth()) {
            if (day_ > date.getDay()) return false;
            else if (day_ < date.getDay()) return true;
            else if (day_ == date.getDay()) {
                if (hour_ > date.getHour()) return false;
                else if (hour_ < date.getHour()) return true;
                else if (hour_  == date.getHour()) {
                    if (minute_ > date.getMinute()) return false;
                    else return true;
                }
            }
        }
    }
    return true;
}
