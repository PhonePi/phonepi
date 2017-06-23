//
// Created by arseny on 15.05.17.
//

#ifndef DAEMON_STRUCT_H
#define DAEMON_STRUCT_H

#include <QMetaType>
#include <QString>
#include <QtDBus>
#include <zconf.h>
#include <sys/stat.h>
#include <syslog.h>

#define INFO 0
#define ERROR -1

static void getAnswer(DBusMessage*, DBusMessageIter);
static void writeLog(const char*, int);


struct Answer_struct{
    QString name;
    QMap<QString, QVariant> porp_map;
};
Q_DECLARE_METATYPE(Answer_struct)

struct g_answer{
    GString name;
    GVariantDict prop_map;
};

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

static void getAnswer(DBusMessage *msg, DBusMessageIter args){
    if (DBUS_TYPE_ARRAY == dbus_message_iter_get_arg_type(&args)) {
        writeLog("Message type - array", INFO);
        DBusMessageIter arrayIter;
        dbus_message_iter_recurse(&args, &arrayIter);
        getAnswer(msg, arrayIter);
    }
    if (DBUS_TYPE_STRUCT == dbus_message_iter_get_arg_type(&args)) {
        DBusMessageIter structIter;
        dbus_message_iter_recurse(&args, &structIter);
        getAnswer(msg, structIter);
    }
    if(DBUS_TYPE_DICT_ENTRY == dbus_message_iter_get_arg_type(&args)) {
        DBusMessageIter dictIter;
        dbus_message_iter_recurse(&args, &dictIter);
        getAnswer(msg, dictIter);
    }
    if(DBUS_TYPE_OBJECT_PATH == dbus_message_iter_get_arg_type(&args)) {
        GObject a;
        dbus_message_iter_get_basic(&args, &a);
        dbus_message_iter_next(&args);
        getAnswer(msg, args);
    }
    if(DBUS_TYPE_STRING == dbus_message_iter_get_arg_type(&args)){
        std::string a;
        dbus_message_iter_get_basic(&args, &a);
        dbus_message_iter_next(&args);
        getAnswer(msg, args);
    }
    if(DBUS_TYPE_VARIANT == dbus_message_iter_get_arg_type(&args)){
        std::string a;
        dbus_message_iter_get_basic(&args, &a);
        dbus_message_iter_next(&args);
        getAnswer(msg, args);
    }


    /*if (!dbus_message_iter_next(&args))
        fprintf(stderr, "Message has too few arguments!\n");
    else if (DBUS_TYPE_UINT32 != dbus_message_iter_get_arg_type(&args))
        fprintf(stderr, "Argument is not int!\n");
    else
        dbus_message_iter_get_basic(&args, &level);

    printf("Got Reply: %d, %d\n", stat, level);*/
}

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
