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

void QDBusCalls::dialNumber(std::string phoneNumber) {
    if(!bus.isConnected())
        exit(1);

    QString number(phoneNumber.c_str());
    qDebug() << number;
    QDBusInterface dbus_iface("org.ofono", selected_modem, "org.ofono.VoiceCallManager", bus);
    QDBusMessage call_status = dbus_iface.call(QDBus::BlockWithGui, "Dial", number, QString("default"));

    if(!isAnswerValid(call_status))
        exit(1);

    qDebug() << call_status;
}
