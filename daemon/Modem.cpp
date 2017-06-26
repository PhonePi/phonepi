#include <dbus/dbus.h>
#include "Modem.h"

Modem::Modem(DBusConnection *connection, std::string preferedModem) {
    this->connection = connection;
    this->preferedModem = preferedModem.c_str();

    getModem();
}

std::vector<g_answer> Modem::allModems() {
    DBusPendingCall *pending;
    DBusMessageIter args;

    DBusMessage *msg = dbus_message_new_method_call("org.ofono", "/", "org.ofono.Manager", "GetModems");
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
    if (!dbus_message_iter_init(msg, &args))
        writeLog("Message has no arguments!\n", INFO);
    std::vector<g_answer> modems;
    modems = getAnswer(msg, args);
    dbus_message_unref(msg);
    return modems;
}

void Modem::getModem() {
    std::vector<g_answer> modems = allModems();
    if(modems.empty()){
        writeLog("No modems were found in the system", ERROR);
        exit(1);
    }

    if (modems.size() == 1) {
        name = modems[0].name;
        for (g_prop props : modems[0].props) {
            if ((*g_string_new("Powered")).str == props.prop_name.str) {
                enabled = props.prop_val.str == "True";
                break;
            }
        }
    } else {
        for (g_answer modem : modems) {
            if ((*g_string_new(preferedModem)).str == modem.name.str) {
                name = modem.name;
                this->props = modem.props;
                for (g_prop props : this->props) {
                    if ((*g_string_new("Powered")).str == props.prop_name.str) {
                        enabled = props.prop_val.str == "True";
                        break;
                    }
                }
            }
        }
    }
    writeLog(strcat(strcat("Modem ", name.str), " powered: ") + enabled, INFO);
}

bool Modem::enableModem() {
    if(enabled)
        return true;

    DBusMessageIter args;
    DBusPendingCall* pending;
    DBusMessage *msg = dbus_message_new_method_call("org.ofono", name.str, "org.ofono.Modem", "SetProperty");
    isMsgValid(msg);

    dbus_message_iter_init_append(msg, &args);
    if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, "Powered") &&
            !dbus_message_iter_append_basic(&args, DBUS_TYPE_BOOLEAN, "True")) {
        writeLog("Out Of Memory!\n", ERROR);
        exit(1);
    }
    if (!dbus_connection_send_with_reply (connection, msg, &pending, -1)) { // -1 is default timeout
        writeLog("Out Of Memory!\n", ERROR);
        exit(1);
    }
    if (NULL == pending) {
        writeLog("Pending Call Null\n", ERROR);
        exit(1);
    }
    dbus_message_unref(msg);
}

