//
// Created by kivi on 23.05.17.
//

#include <dirent.h>
#include <iostream>
#include <QDir>

#include "Config.h"

inline bool ends_with(std::string const & value, std::string const & ending) {
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

Config::Config(const std::string conffile): conf_(conffile) {}

std::string Config::getBackgroung() {
    return conf_.Get("desktop", "background", "");
}

std::vector<Applicaton> Config::getApplications() {
    std::vector<Applicaton> apps;
    auto desktopEntryDir = conf_.Get("apps", "entry-dir", "");
    if (desktopEntryDir.empty()) return apps;

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (desktopEntryDir.c_str())) == NULL) {
        return apps;
    }

    /* print all the files and directories within directory */
    QDir directory(QString(desktopEntryDir.c_str()));
    while ((ent = readdir (dir)) != NULL) {
        if (ent->d_type == DT_REG) {
            std::string filename(ent->d_name);
            if (not ends_with(filename, ".entry")) continue;

            INIReader entryconf(directory.filePath(QString(filename.c_str())).toStdString());
            std::string icon = entryconf.Get("entry", "icon", "");
            std::string name = entryconf.Get("entry", "name", "");
            std::string executable = entryconf.Get("entry", "exe", "");
            if (not executable.empty())
                apps.push_back({name, icon, executable});
        }
    }
    closedir (dir);
    return std::move(apps);
}

int Config::getIconsize() {
    return (int)conf_.GetInteger("desktop", "iconsize", 70);
}

int Config::getDesktopRows() {
    return (int)conf_.GetInteger("desktop", "rows", 7);
}

int Config::getDesktopColumns() {
    return (int)conf_.GetInteger("desktop", "columns", 4);
}

int Config::getFontSize() {
    return (int)conf_.GetInteger("desktop", "fontsize", 16);
}

std::string Config::getFontColor() {
    return conf_.Get("desktop", "fontcolor", "White");
}
