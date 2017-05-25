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
#include "AdaptorVoiceCallManager.h"
#include "ProxyVoiceCallManager.h"

Handler::Handler(QObject *parent): QObject(parent){}

Handler::~Handler(){}

void Handler::setUpHandler(QDBusConnection bus, QString current_modem){
    if(!bus.isConnected())
        exit(1);

    QDBusInterface dbus_iface("org.ofono", current_modem, "org.ofono.VoiceCallManager", bus);
    QDBusMessage calls = dbus_iface.call("GetCalls");

    if(QDBusMessage::ErrorMessage == calls.type()){
        writeLog(calls.errorMessage().toLatin1(), ERROR);
        exit(1);
     }

    new VoiceCallManagerAdaptor(this);
    auto reply = QDBusConnection::sessionBus().registerObject("/CallHandler", this);
    if(reply)
        writeLog("Handler | Succesfully register!", INFO);
    else{
        writeLog("Handler | Register failed", ERROR);
        exit(1);
    }

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
