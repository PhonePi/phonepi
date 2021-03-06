//
// Created by kivi on 23.05.17.
//

#ifndef DESKTOP_CONFIG_H
#define DESKTOP_CONFIG_H

#include <vector>

#include "INIReader.h"

struct Applicaton {
    std::string name;
    std::string icon;
    std::string path;
    std::string executable;
};

class Config {

public:

    static const std::string DEFAULT_CONFIG;

    Config(const std::string conffile);
    Config() : Config(DEFAULT_CONFIG) {}

    int getIconsize();
    int getFontSize();
    std::string getFontColor();
    int getDesktopRows();
    int getDesktopColumns();
    std::string getBackgroung();
    std::vector<Applicaton> getApplications();

private:

    INIReader conf_;

};


#endif //DESKTOP_CONFIG_H
