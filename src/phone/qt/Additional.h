//
// Created by arseny on 7/5/17.
//

#ifndef DIALER_PI_ADDITIONAL_H
#define DIALER_PI_ADDITIONAL_H

#include <pwd.h>
#include <zconf.h>
#include <iostream>
#include <QScreen>
#include <QPalette>
#include <QWidget>


static std::string workingDir = "~//Repos//KSPT//Phone//src//phone//qt//";

static std::string get_fullpath(std::string path) {
    if (path[0] == '~') {
        struct passwd *pw = getpwuid(getuid());
        std::string fullpath = std::string(pw->pw_dir);
        fullpath += std::string(path.begin() + 1, path.end());
        return fullpath;
    }
    return path;
}

static std::string get_icoPath(std::string path){
    return get_fullpath(workingDir + "pics//" + path);
}

static QSize getScreenSize(){
    QSize screenSize;
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    screenSize.setWidth(screenGeometry.width());
    screenSize.setHeight(screenGeometry.height());
    return  screenSize;
}

static QPalette getCommonPalette(QWidget* widget){
    QPalette pal(widget->palette());
    pal.setColor(QPalette::Background, "#fbf1c7");
    return pal;
}



#endif //DIALER_PI_ADDITIONAL_H
