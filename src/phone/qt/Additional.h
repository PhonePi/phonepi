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
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusInterface>
#include <QDebug>
#include <sys/stat.h>


static std::string workingDir = "~//phonepi//src//phone//qt//";
static QDBusConnection bus = QDBusConnection::systemBus();

static QWidget* currentWidget;
static QWidget* currentClass;

static QString getSimPath(){
    struct stat buf;

    if(stat(std::string("/usr/share/phonepi/info").c_str(), &buf) != 0){
        qDebug() << "Cannot find file /usr/share/pnonepi/info";
        qDebug() << "For correct work of dialer app sim-module is required";
        exit(1);
    }

    char buffer[20];
    std::string result = "";
    FILE* pipe = popen(
            "cat /usr/share/phonepi/info | grep Modem | awk '{ print $2 }'", "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != NULL)
                result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    QString selected_modem = result.c_str();
    return selected_modem = selected_modem.toStdString()
            .substr(0, selected_modem.toStdString().size() -1).c_str();
}

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

static void makeCall(QString number){
    if(!bus.isConnected()){
        qDebug() << "Connection is not established";
        exit(1);
    }

    QDBusInterface dbus_iface("org.ofono", getSimPath(), "org.ofono.VoiceCallManager", bus);
    dbus_iface.call(QDBus::Block, "Dial", QVariant::fromValue(QString(number)),
                    QVariant::fromValue(QString("")));
}

static void answerCall(QString voiceCallPath){
    if(!bus.isConnected()){
        qDebug() << "Connection is not established";
        exit(1);
    }

    QDBusInterface dbus_iface("org.ofono", voiceCallPath, "org.ofono.VoiceCall", bus);
    dbus_iface.call(QDBus::Block, "Aswer");
}

static void hangUp(){
    if(!bus.isConnected()){
        qDebug() << "Connection is not established";
        exit(1);
    }

    QDBusInterface dbus_iface("org.ofono", getSimPath(), "org.ofono.VoiceCallManager", bus);
    dbus_iface.call(QDBus::Block, "HangupAll");
}

static void setWidgetInfo(QWidget* widget, QWidget* widget1){
    currentWidget = widget;
    currentClass = widget1;
}

static void signalHandler(int signum){
    DialerWindow *dialerWindow = new DialerWindow();
    dialerWindow->showDialer();
    currentWidget->close();
    delete(currentWidget);
    delete(currentClass);
}



#endif //DIALER_PI_ADDITIONAL_H
