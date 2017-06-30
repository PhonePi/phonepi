//
// Created by kivi on 30.06.17.
//

#include <ctime>
#include <sstream>
#include <iostream>
#include <chrono>
#include <thread>

#include "Timer.h"

std::string double_digit(int num) {
    std::ostringstream ss;
    if (num < 10) {
        ss << "0" << num;
    } else ss << num;
    return ss.str();
}

std::string getCurrentTime() {
    static const std::string DAY[]= {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    static const std::string MONTH[]= {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    time_t t = time(0);
    struct tm * now = localtime( & t );
    std::ostringstream ss;
    ss << double_digit(now->tm_hour) << ':' << double_digit(now->tm_min) << std::endl;
    ss << DAY[now->tm_wday] << ", " << now->tm_mday << " " << MONTH[now->tm_mon];
    return ss.str();
}

void Timer::start() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        emit updateTime(getCurrentTime().c_str());
    }
}
