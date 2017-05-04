#include "QDBusCalls.h"

QDBusCalls::QDBusCalls() {
    if(!bus.isConnected())
        exit(1);

    QDBusInterface dbus_iface("org.ofono", "/", "org.ofono.Manager", bus);

    QDBusMessage modem = dbus_iface.call("GetModems");

    if(!isAnswerValid(modem))
        exit(1);

    const QDBusArgument &dbusArgs = modem.arguments().first().value<QDBusArgument>();

    getModemAnswer(dbusArgs);
}


bool QDBusCalls::isAnswerValid(QDBusMessage msg) {
    if(QDBusMessage::ErrorMessage == msg.type()){
        qDebug() << msg.errorMessage();
        return false;
    }
    return true;
}

void QDBusCalls::getModemAnswer(const QDBusArgument &dbusArgs) {
    std::vector<Modem_struct> modems;
    dbusArgs.beginArray();
    while (!dbusArgs.atEnd()) {
        dbusArgs.beginStructure();
        if (dbusArgs.currentType() == 0)
            dbusArgs >> modem_struct.name;
        if (dbusArgs.currentType() == 4)
            dbusArgs >> modem_struct.porp_map;
        dbusArgs.endStructure();
        modems.push_back(modem_struct);
    }
    dbusArgs.endArray();

    qDebug() << modems.size();

    if(modems.size() == 1)
        selected_modem = modems[0].name;
    else{
        for(Modem_struct modem : modems)
            if(modem.name.contains("sim900")) {
                selected_modem = modem.name;
                break;
            }
    }

    qDebug() << selected_modem;
}

void QDBusCalls::dialNumber(const char* phoneNumber) {
    if(!bus.isConnected())
        exit(1);

    QVariant number(QVariant::String);
    QList<QVariant>args;
    QDBusInterface dbus_iface("org.ofono", selected_modem, "org.ofono.VoiceCallManager", bus);
    number = phoneNumber;
    args.append(phoneNumber);
    args.append("");
    QDBusMessage call_status = dbus_iface.callWithArgumentList(QDBus::BlockWithGui,
                                                               "Dial", args);
    if(!isAnswerValid(call_status))
        return;
}

void QDBusCalls::hangup(){
    QDBusInterface dbus_iface("org.ofono", selected_modem, "org.ofono.VoiceCallManager", bus);
    QDBusMessage msg = dbus_iface.call("HangupAll");
    qDebug() << "Calls hanged up";
}

