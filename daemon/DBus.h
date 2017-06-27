#ifndef DAEMON_DBUS_H
#define DAEMON_DBUS_H

#include <iostream>
#include <glib.h>
#include <dbus/dbus.h>
#include <dbus/dbus-glib-lowlevel.h>
#include <vector>
#include "Additional.h"

class DBus {
private:
    DBusConnection *connection;
    DBusError error;
    g_prop props;
    bool value = false;
    bool isMsgValid(DBusMessage *);
    static DBusHandlerResult callback(DBusConnection *, DBusMessage *, void *);

public:
    g_answer answer;
    DBus();
    /*std::vector<g_answer> */void getAnswer(DBusMessage*, DBusMessageIter, std::vector<g_answer>*);
    DBusMessage* methodCall(const char*, const char*, const char*, const char*);
    void methodCallSetBoolProp(const char*, const char*, const char*, const char*, std::string, dbus_bool_t);
    int setUpHandler(const char*);
};


#endif //DAEMON_DBUS_H
