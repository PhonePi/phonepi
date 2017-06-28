#include <dbus/dbus.h>
#include <fstream>
#include <pwd.h>
#include "Modem.h"

Modem::Modem(DBus* dbus_class, std::string preferedModem) {
    this->dbus_class = *dbus_class;
    this->preferedModem = preferedModem;

    getModem();
}

std::vector<g_answer> Modem::allModems() {
    DBusMessage *msg = dbus_class.methodCall(std::string("org.ofono").c_str(),
                                             std::string("/").c_str(), std::string("org.ofono.Manager").c_str(),
                                             std::string("GetModems").c_str());
    DBusMessageIter args;
    if (!dbus_message_iter_init(msg, &args))
        writeLog("Message has no arguments!\n", INFO);
    std::vector<g_answer> modems;
    dbus_class.getAnswer(msg, args, &modems);
    dbus_message_unref(msg);
    return modems;
}

void Modem::getModem() {
    std::vector<g_answer> modems = allModems();
    if(modems.empty()){
        writeLog("No modems were found in the system", ERROR);
        ENDOFLOG;
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
                        enabled = std::string(props.prop_val.str) == "True";
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

    const char* path = std::string(name.str).c_str();
    dbus_class.methodCallSetBoolProp(std::string("org.ofono").c_str(), path,
                                     std::string("org.ofono.Modem").c_str(), std::string("SetProperty").c_str(),
                                     std::string("Powered"), TRUE);
    getModem();
    if(!enabled){
        writeLog("Enabling failed. Daemon stops", ERROR);
        ENDOFLOG;
        exit(1);
    } else
        writeLog("Enable succeed", INFO);
}

void Modem::getOperator() {
    std::string path = std::string(name.str);
    DBusMessage *msg = dbus_class.methodCall(std::string("org.ofono").c_str(), path.c_str(),
                          std::string("org.ofono.NetworkRegistration").c_str(), std::string("GetOperators").c_str());
    DBusMessageIter args;

    if (!dbus_message_iter_init(msg, &args))
        writeLog("Message has no arguments!\n", INFO);
    std::vector<g_answer> operators;
    dbus_class.getAnswer(msg, args, &operators);
    dbus_message_unref(msg);

    for(g_prop prop : operators[0].props){
        if("Name" == std::string(prop.prop_name.str))
            currentOPerator = std::string(prop.prop_val.str);
    }

    struct passwd *pw = getpwuid(getuid());
    const char *homedir = pw->pw_dir;

    std::ofstream operName (std::string(homedir) + "//.operator");
    if(!operName){
        writeLog("Cannot open .operator file", ERROR);
        exit(1);
    }

    operName << currentOPerator << std::endl;
    operName.close();

    writeLog((std::string("Current operator: ") + currentOPerator).c_str(), INFO);
}

int Modem::getCalls() {
    dbus_class.methodCall("org.ofono", "/", "org.ofono.Manager", "GetCalls");
    const char *rule = std::string("type='signal', interface='org.ofono.VoiceCallManager'").c_str();
    return dbus_class.setUpHandler(rule);
}

