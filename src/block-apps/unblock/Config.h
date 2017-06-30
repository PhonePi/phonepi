//
// Created by kivi on 23.05.17.
//

#ifndef DESKTOP_CONFIG_H
#define DESKTOP_CONFIG_H

#include <vector>

#include "INIReader.h"

class Config {

public:

    static const std::string DEFAULT_CONFIG;

    Config(const std::string conffile);
    Config() : Config(DEFAULT_CONFIG) {}

    std::string getBackgroung();
    int getFontSize();
    std::string getFontColor();
    std::string getBlockProcess();

private:

    INIReader conf_;

};


#endif //DESKTOP_CONFIG_H
