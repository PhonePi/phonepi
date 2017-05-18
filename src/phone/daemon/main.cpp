#include <iostream>
#include <QString>
#include <QtDBus>
#include "Struct.h"
#include "Handler.h"

#define INFO 0
#define ERROR -1

bool isAnswerValid(QDBusMessage);
int callsMonitor(QDBusConnection, QString);
QVariant isModemEnabled = "false";
void writeLog(const char*, int);

int main() {

    writeLog("Start calls daemon", INFO);
    QDBusConnection bus = QDBusConnection::systemBus();

    if(!bus.isConnected())
        exit(1);

    QDBusInterface dbus_iface("org.ofono", "/", "org.ofono.Manager", bus);
    QDBusMessage modem = dbus_iface.call("GetModems");

    if(!isAnswerValid(modem))
        exit(1);

    const QDBusArgument &dbusArgs = modem.arguments().first().value<QDBusArgument>();
    std::vector<Answer_struct> answers = getStructAnswer(dbusArgs);
    QString selected_modem;

    if(answers.size() == 0){
        writeLog("Answer is NULL", ERROR);
        exit(1);
    }


    if(answers.size() == 1) {
        selected_modem = answers[0].name;
        isModemEnabled = answers[0].porp_map["Powered"];
        writeLog("Modem powered: " + isModemEnabled.toString().toLatin1(), INFO);
    }else
        for(Answer_struct modem : answers)
            if(modem.name.contains("sim900")){
                selected_modem = modem.name;
                isModemEnabled = modem.porp_map["Powered"].toBool();
                writeLog("Modem powered: " + isModemEnabled.toString().toLatin1(), INFO);
            }


    if(selected_modem.isNull() || selected_modem.isEmpty()) {
        writeLog("No modem was selected", ERROR);
        exit(1);
    }


    writeLog("Selected modem: " + selected_modem.toLatin1(), INFO);

    if(isModemEnabled == "false") {
        QList<QVariant> args;
        QDBusInterface enable_iface("org.ofono", selected_modem, "org.ofono.Modem", bus);
        args.append("Powered");
        args.append(QVariant::fromValue(QDBusVariant("true")));
        QDBusMessage modem_status = dbus_iface.callWithArgumentList(QDBus::BlockWithGui,
                                                                    "SetProperty", args);

        if (!isAnswerValid(modem_status))
            exit(1);

        writeLog("Modem succesffuly enabled", INFO);
    }

    int pid = fork();
    if(pid == -1) {
        writeLog("Daemon launching failed.\n", ERROR);
        return -1;
    }
    else if(!pid){
        umask(0);
        setsid();
        chdir("/");

        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);

        return callsMonitor(bus, selected_modem);

    } else
        return 0;
}

bool isAnswerValid(QDBusMessage msg) {
    if(QDBusMessage::ErrorMessage == msg.type()){
        writeLog(msg.errorMessage().toLatin1(), ERROR);
        return false;
    }
    return true;
}

int callsMonitor(QDBusConnection bus, QString current_modem){
    Handler handler;
    handler.setUpHandler(bus, current_modem);

    writeLog("Daemon ends", ERROR);
}
