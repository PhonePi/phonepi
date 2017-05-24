//
// Created by arseny on 15.05.17.
//

#include <QDBusConnection>
#include <QDBusInterface>
#include <QtCore/QMetaObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include "Handler.h"
#include "Struct.h"
#include "OfonoVoiceCallManagerAdaptor.h"
#include "VoiceCallManager.h"

Handler::Handler(QObject *parent): QObject(parent){}

Handler::~Handler(){}

void Handler::setUpHandler(QDBusConnection bus, QString current_modem){
    if(!bus.isConnected())
        exit(1);

    VoiceCallManagerAdaptor *voiceCall = new VoiceCallManagerAdaptor(this);
    auto reply = QDBusConnection::sessionBus().registerObject("/handler", this);
    if(reply)
        writeLog("Handler | Succesfully register!", INFO);
    else{
        writeLog("Handler | Register failed", ERROR);
        exit(1);
    }

    voiceCall->blockSignals(false);
    voiceCall->GetCalls();
    org::ofono::VoiceCallManager *iface;
    iface = new org::ofono::VoiceCallManager(QString(), current_modem, QDBusConnection::sessionBus(), this);
    connect(iface, SIGNAL(CallAdded(QDBusObjectPath&, QVariantMap& )), this, SLOT(callAdded(QDBusObjectPath,QVariantMap)));

    writeLog("Write log", INFO);

    while(true){}
}

void Handler::callAdded(const QDBusObjectPath& path, const QVariantMap& props) {
    writeLog("callAdded SLOT", INFO);
    system("GUI/Phone/src/phone/qt/phone");
}

void Handler::callRemoved(QString path){
    writeLog("callRemoved SLOT", INFO);
}
