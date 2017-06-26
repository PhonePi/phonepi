//
// Created by arseny on 6/26/17.
//

#ifndef DAEMON_MODEM_H
#define DAEMON_MODEM_H

#include <iostream>
#include <glib.h>
#include <dbus/dbus.h>
#include <dbus/dbus-glib-lowlevel.h>
#include <vector>
#include "Struct.h"

class Modem {
private:
    GString name;
    std::vector<g_prop> props;
    bool enabled = false;
    DBusConnection *connection;
    std::string preferedModem;
    std::vector<g_answer> allModems();
    void getModem();


public:
    Modem(DBusConnection*, std::string);
    void enableModem();
    void getOperator();
};


#endif //DAEMON_MODEM_H
