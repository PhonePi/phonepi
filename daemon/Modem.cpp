#include <dbus/dbus.h>
#include "Modem.h"

Modem::Modem(DBusConnection *connection, std::string preferedModem) {
    this->connection = connection;
    this->preferedModem = preferedModem;

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
            if(preferedModem == std::string(modem.name.str)){
                name = modem.name;
                this->props = modem.props;
                for (g_prop props : this->props) {
                    if ("Powered" == std::string(props.prop_name.str)){
                        enabled = props.prop_val.str == "True";
                        break;
                    }
                }
                break;
            }
        }
    }

    std::string msg = std::string("Modem ") + name.str + " powered state: " +
            (enabled ? "True" : "False");
    writeLog(msg.c_str(), INFO);
}

void Modem::enableModem() {
    if(enabled)
        return;

    DBusMessageIter args, subIter;
    DBusPendingCall* pending;
    DBusMessage *msg = dbus_message_new_method_call("org.ofono", name.str, "org.ofono.Modem", "SetProperty");
    isMsgValid(msg);

    dbus_bool_t bolVal = TRUE;
    std::string prop = "Powered";
    dbus_message_iter_init_append(msg, &args);
    dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &prop);

    dbus_message_iter_open_container(&args, DBUS_TYPE_VARIANT, DBUS_TYPE_BOOLEAN_AS_STRING, &subIter);
    dbus_message_iter_append_basic(&subIter, DBUS_TYPE_BOOLEAN, &bolVal);

    dbus_message_iter_close_container(&args, &subIter);

    if (!dbus_connection_send_with_reply (connection, msg, &pending, -1)) { // -1 is default timeout
        writeLog("Out Of Memory!\n", ERROR);
        exit(1);
    }
    if (NULL == pending) {
        writeLog("Pending Call Null\n", ERROR);
        exit(1);
    }
    dbus_message_unref(msg);
    enabled = true;
    writeLog("Modem was successfully enabled", INFO);
}

