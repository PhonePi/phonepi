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
#include "Additional.h"
#include "DBus.h"

class Modem {
private:
    GString name;
    std::vector<g_prop> props;
    bool enabled = false;
    DBus dbus_class;
    std::string preferedModem;
    std::string currentOPerator;
    std::vector<g_answer> allModems();
    void getModem();

public:
    Modem(DBus, std::string);
    void enableModem();
    void getOperator();
    int getCalls();
};


#endif //DAEMON_MODEM_H
