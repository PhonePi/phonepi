//
// Created by arseny on 6/27/17.
//

#include <cstdlib>
#include "DBus.h"

DBus::DBus() {
    dbus_error_init(&error);
    connection = dbus_bus_get(DBUS_BUS_SYSTEM, &error);

    if (dbus_error_is_set(&error)) {
        char* msg;
        strcpy(msg, "Cannot get System BUS connection: ");
        strcat(msg, error.message);
        writeLog(msg, ERROR);
        dbus_error_free(&error);
        exit(1);
    }
    writeLog("Succesfull System BUS connection", INFO);
}

/*std::vector<g_answer>*/void DBus::getAnswer(DBusMessage *msg, DBusMessageIter args, std::vector<g_answer> *answ){
    if (DBUS_TYPE_ARRAY == dbus_message_iter_get_arg_type(&args)) {
        DBusMessageIter arrayIter;
        dbus_message_iter_recurse(&args, &arrayIter);
        do {
            getAnswer(msg, arrayIter, answ);
        }while (dbus_message_iter_next(&arrayIter));

    }
    if (DBUS_TYPE_STRUCT == dbus_message_iter_get_arg_type(&args)) {
        DBusMessageIter structIter;
        dbus_message_iter_recurse(&args, &structIter);
        getAnswer(msg, structIter, answ);
        answ->push_back(answer);
        answer.props.clear();
    }
    if(DBUS_TYPE_DICT_ENTRY == dbus_message_iter_get_arg_type(&args)) {
        DBusMessageIter dictIter;
        dbus_message_iter_recurse(&args, &dictIter);
        getAnswer(msg, dictIter, answ);
        answer.props.push_back(props);
        dbus_message_iter_next(&args);
    }
    if(DBUS_TYPE_VARIANT == dbus_message_iter_get_arg_type(&args)){
        DBusMessageIter variant;
        dbus_message_iter_recurse(&args, &variant);
        value = true;
        getAnswer(msg, variant, answ);
        value = false;
    }

    if(DBUS_TYPE_OBJECT_PATH == dbus_message_iter_get_arg_type(&args)) {
        GString a;
        dbus_message_iter_get_basic(&args, &a);
        answer.name = a;
        dbus_message_iter_next(&args);
        getAnswer(msg, args, answ);
    }
    if(DBUS_TYPE_STRING == dbus_message_iter_get_arg_type(&args)) {
        GString a;
        dbus_message_iter_get_basic(&args, &a);
        if(value)
            props.prop_val = a;

        else
            props.prop_name = a;

        if (!dbus_message_iter_has_next(&args))
            return;
        dbus_message_iter_next(&args);
        getAnswer(msg, args, answ);
    }
    if(DBUS_TYPE_BOOLEAN == dbus_message_iter_get_arg_type(&args)){
        bool val;
        dbus_message_iter_get_basic(&args, &val);
        props.prop_val = *g_string_new(val ? "True" : "False");
        if(!dbus_message_iter_has_next(&args))
            return;
        dbus_message_iter_next(&args);
        getAnswer(msg, args, answ);
    }
    return;
}

bool DBus::isMsgValid(DBusMessage *msg) {
    if (NULL == msg) {
        writeLog("Message Null\n", ERROR);
        exit(1);
    }
    return true;
}

DBusMessage* DBus::methodCall(const char* busName, const char* path, const char* iface, const char* method){
    DBusPendingCall* pending;
    DBusMessage *msg = dbus_message_new_method_call(busName, path,
                                                    iface, method);
    isMsgValid(msg);

    if (!dbus_connection_send_with_reply(connection, msg, &pending, 1500)) {
        writeLog("Out Of Memory!\n", ERROR);
        exit(1);
    }
    if (NULL == pending) {
        writeLog("Pending Call Null\n", ERROR);
        exit(1);
    }
    dbus_message_unref(msg);
    dbus_pending_call_block(pending);
    msg = dbus_pending_call_steal_reply(pending);

    isMsgValid(msg);
    dbus_pending_call_unref(pending);
    return msg;
}

void DBus::methodCallSetBoolProp(const char* busName, const char* path, const char* iface, const char* method,
                                 std::string prop, dbus_bool_t boolVal){
    DBusMessageIter args, subIter;
    DBusPendingCall* pending;
    DBusMessage *msg = dbus_message_new_method_call(busName, path, iface, method);
    isMsgValid(msg);

    dbus_message_iter_init_append(msg, &args);
    dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &prop);

    dbus_message_iter_open_container(&args, DBUS_TYPE_VARIANT, DBUS_TYPE_BOOLEAN_AS_STRING, &subIter);
    dbus_message_iter_append_basic(&subIter, DBUS_TYPE_BOOLEAN, &boolVal);

    dbus_message_iter_close_container(&args, &subIter);

    if (!dbus_connection_send_with_reply (connection, msg, &pending, -1)) {
        writeLog("Out Of Memory!\n", ERROR);
        exit(1);
    }
    if (NULL == pending) {
        writeLog("Pending Call Null\n", ERROR);
        exit(1);
    }
    dbus_message_unref(msg);
}

DBusHandlerResult DBus::callback(DBusConnection *conn, DBusMessage *msg, void *user_data) {
    if(dbus_message_is_signal(msg, "org.ofono.VoiceCallManager", "CallAdded"))
        writeLog("CallAdded callback", INFO);

    if(dbus_message_is_signal(msg, "org.ofono.VoiceCallManager", "CallRemoved"))
        writeLog("CallRemoved callback", INFO);

    return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}

int DBus::setUpHandler(const char * rule) {
    writeLog("Handler settings", INFO);
    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    dbus_connection_setup_with_g_main(connection, NULL);

    dbus_bus_add_match(connection, rule, &error);

    if(dbus_error_is_set(&error)){
        char* msg;
        strcpy(msg, "Cannot add D-BUS match rule, cause: ");
        strcat(msg, error.message);
        writeLog(msg, ERROR);
        dbus_error_free(&error);
        return EXIT_FAILURE;
    }

    writeLog(std::string("Listening to D-BUS signals using a connection filter").c_str(), INFO);
    dbus_connection_add_filter(connection, DBus::callback, NULL, NULL);

    g_main_loop_run(loop);

    return EXIT_SUCCESS;
}