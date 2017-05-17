//
// Created by arseny on 15.05.17.
//

#include <QDBusConnection>
#include <QDBusInterface>
#include "Handler.h"
#include "Struct.h"

Handler::Handler(QDBusConnection bus, QString current_modem) {
    if(!bus.isConnected())
        exit(1);

    QDBusInterface dbus_iface("org.ofono", current_modem, "org.ofono.VoiceCallManager", bus);
    QDBusMessage calls = dbus_iface.call("GetCalls");

    if(QDBusMessage::ErrorMessage == calls.type()){
        exit(1);
    }

    writeLog("Connection to the signals", INFO);

    bus.connect("org.ofono", current_modem, "org.ofono.VoiceCallManager", "CallAdded",
            this, SLOT(callAdded(QString, QMap<QString,QVariant>)));
    bus.connect("org.ofono", current_modem, "org.ofono.VoiceCallManager", "CallRemoved",
                this, SLOT(callRemoved(QString)));
}

void Handler::callAdded(QString path, QMap<QString, QVariant> props) {
    writeLog("callAdded SLOT", INFO);
    QVariant number = props[QString("LineIdentification")];
    if(props["State"].toString().contains("incoming"))
        writeLog("Incoming call", INFO);

    phoneNumber = number.toString();
}

void Handler::callRemoved(QString path){
    writeLog("callRemoved SLOT", INFO);
    writeLog("Call was removed SLOT", INFO);

}

