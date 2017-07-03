//
// Created by kivi on 23.05.17.
//

#include <dirent.h>
#include <iostream>
#include <QDir>
#include <pwd.h>
#include <unistd.h>

#include "Config.h"

std::string get_fullpath(const std::string path) {
    if (path[0] == '~') {
        struct passwd *pw = getpwuid(getuid());
        std::string fullpath = std::string(pw->pw_dir);
        fullpath += std::string(path.begin() + 1, path.end());
        return fullpath;
    }
    return path;
}

inline bool ends_with(std::string const & value, std::string const & ending) {
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

Config::Config(const std::string conffile): conf_(get_fullpath(conffile)) {}

std::string Config::getBackgroung() {
    return get_fullpath(conf_.Get("screen", "background", ""));
}

int Config::getFontSize() {
    return (int)conf_.GetInteger("screen", "fontsize", 16);
}

std::string Config::getFontColor() {
    return conf_.Get("screen", "fontcolor", "White");
}

std::string Config::getBlockProcess() {
    return conf_.Get("block", "exe", "White");
}

const std::string Config::DEFAULT_CONFIG = "~/.config/unblock-pi";