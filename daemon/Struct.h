
//
// Created by arseny on 15.05.17.
//

#ifndef DAEMON_STRUCT_H
#define DAEMON_STRUCT_H

#include <vector>
#include <map>
#include <QMetaType>
#include <QString>
#include <QtDBus>
#include <zconf.h>
#include <sys/stat.h>
#include <syslog.h>

#define INFO 0
#define ERROR -1

struct Answer_struct{
    QString name;
    QMap<QString, QVariant> porp_map;
};
Q_DECLARE_METATYPE(Answer_struct)

struct g_prop{
    GString prop_name;
    GString prop_val;
}props;

struct g_answer{
    GString name;
    std::vector<g_prop> props;
}stru;

std::vector<g_answer> answ;
bool value = false;

static void writeLog(const char* message, int status) {
    openlog("calls_daemon", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);

    switch(status){
        case ERROR:
            syslog(LOG_ERR, message);
            break;
        case INFO:
            syslog(LOG_INFO, message);
            break;
        default:
            syslog(LOG_ALERT, message);
            break;
    }
    closelog();
}

static std::vector<Answer_struct> getStructAnswer(const QDBusArgument &dbusArgs) {
    QString selected_modem;
    Answer_struct answer_struct;
    std::vector<Answer_struct> answers;
    dbusArgs.beginArray();
    while (!dbusArgs.atEnd()) {
        dbusArgs.beginStructure();
        if (dbusArgs.currentType() == 0)
            dbusArgs >> answer_struct.name;
        if (dbusArgs.currentType() == 4)
            dbusArgs >> answer_struct.porp_map;
        dbusArgs.endStructure();
        answers.push_back(answer_struct);
    }
    dbusArgs.endArray();

    return answers;
}

static std::vector<g_answer> getAnswer(DBusMessage *msg, DBusMessageIter args){
    if (DBUS_TYPE_ARRAY == dbus_message_iter_get_arg_type(&args)) {
        DBusMessageIter arrayIter;
        dbus_message_iter_recurse(&args, &arrayIter);
        do {
            getAnswer(msg, arrayIter);
        }while (dbus_message_iter_next(&arrayIter));
    }
    if (DBUS_TYPE_STRUCT == dbus_message_iter_get_arg_type(&args)) {
        DBusMessageIter structIter;
        dbus_message_iter_recurse(&args, &structIter);
        getAnswer(msg, structIter);
        answ.push_back(stru);
    }
    if(DBUS_TYPE_DICT_ENTRY == dbus_message_iter_get_arg_type(&args)) {
        DBusMessageIter dictIter;
        dbus_message_iter_recurse(&args, &dictIter);
        getAnswer(msg, dictIter);
        stru.props.push_back(props);
        dbus_message_iter_next(&args);
    }
    if(DBUS_TYPE_VARIANT == dbus_message_iter_get_arg_type(&args)){
        DBusMessageIter variant;
        dbus_message_iter_recurse(&args, &variant);
        value = true;
        getAnswer(msg, variant);
        value = false;
    }

    if(DBUS_TYPE_OBJECT_PATH == dbus_message_iter_get_arg_type(&args)) {
        GString a;
        dbus_message_iter_get_basic(&args, &a);
        stru.name = a;
        dbus_message_iter_next(&args);
        getAnswer(msg, args);
    }
    if(DBUS_TYPE_STRING == dbus_message_iter_get_arg_type(&args)) {
        GString a;
        dbus_message_iter_get_basic(&args, &a);
        if(value)
            props.prop_val = a;

        else
            props.prop_name = a;

        if (!dbus_message_iter_has_next(&args))
            return answ;
        dbus_message_iter_next(&args);
        getAnswer(msg, args);
    }
    if(DBUS_TYPE_BOOLEAN == dbus_message_iter_get_arg_type(&args)){
        bool val;
        dbus_message_iter_get_basic(&args, &val);
        props.prop_val = *g_string_new(val ? "True" : "False");
        if(!dbus_message_iter_has_next(&args))
            return answ;
        dbus_message_iter_next(&args);
        getAnswer(msg, args);
    }

    return answ;
}



static DBusConnection* connectToBus(DBusError error){
    dbus_error_init(&error);
    DBusConnection *conn = dbus_bus_get(DBUS_BUS_SYSTEM, &error);

    if(dbus_error_is_set(&error)){
        writeLog(strcat("Cannot get System BUS connection: ", error.message), ERROR);
        dbus_error_free(&error);
        exit(1);
        //return EXIT_FAILURE;
    }
    writeLog("Succesfull System BUS connection", INFO);
    return conn;
}

static void isMsgValid(DBusMessage *msg){
    if (NULL == msg) {
        writeLog("Message Null\n", ERROR);
        exit(1);
    }
}
#endif //DAEMON_STRUCT_H
