//
// Created by arseny on 15.05.17.
//

#include <QDBusConnection>
#include <QDBusInterface>
#include "Handler.h"
#include "Struct.h"

Handler::~Handler(){}

void Handler::setUpHandler(QDBusConnection bus, QString current_modem){
    if(!bus.isConnected())
        exit(1);

    QDBusInterface dbus_iface("org.ofono", current_modem, "org.ofono.VoiceCallManager", bus);
    QDBusMessage calls = dbus_iface.call("GetCalls");

    if(QDBusMessage::ErrorMessage == calls.type()){
        exit(1);
    }

    bool callAddedAnswer = bus.connect("org.ofono", current_modem,
                                       "org.ofono.VoiceCallManager", "CallAdded", this,
                                       SLOT(callAdded(const QString&, const QMap<QString,QVariant>&)));
    bool callRemovedAnswer = bus.connect("org.ofono", current_modem,
                                         "org.ofono.VoiceCallManager", "CallRemoved",
                                         this, SLOT(callRemoved(QString)));

    if(!callRemovedAnswer){
        writeLog("CallRemoved connection failed", ERROR);
        exit(1);
    }else
	    writeLog("CallRemoved connection succeed", INFO);

    if(!callAddedAnswer){
        writeLog("CallAdded connection failed", ERROR);
        exit(1);
    }else
	    writeLog("CallAdded connection succeed", INFO);

    while(true){}
}

void Handler::callAdded(const QString& path, const QMap<QString, QVariant>& props) {
    writeLog("callAdded SLOT", INFO);
    if(props["State"].toString().contains("incoming"))
        writeLog("Incoming call from " + props[QString("LineIdentification")]
                                                 .toString().toLatin1(), INFO);
}

void Handler::callRemoved(QString path){
    writeLog("callRemoved SLOT", INFO);
}