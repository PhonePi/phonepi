//
// Created by arseny on 15.05.17.
//

#include <QDBusConnection>
#include <QDBusInterface>
#include "Handler.h"
#include "Struct.h"
#include "OfonoVoiceCallManagerAdaptor.h"

Handler::Handler(QObject *parent): QObject(parent){}

Handler::~Handler(){}

void Handler::setUpHandler(QDBusConnection bus, QString current_modem){
    if(!bus.isConnected())
        exit(1);


    bus.registerObject("/", this);
    VoiceCallManagerAdaptor voiceCall(this);
    //OrgOfonoVoiceCallManagerInterface m_voicecall("org.ofono",current_modem, bus);
    //QDBusInterface dbus_iface("org.ofono", current_modem, "org.ofono.VoiceCallManager", bus);
    //QDBusMessage calls = dbus_iface.call("GetCalls");
    //auto calls = m_voicecall.GetCalls();
    voiceCall.GetCalls();



    //m_voicecall.connect(&m_voicecall, SIGNAL(CallAdded(const QString&, const QVariantMap&)),
      //      this, SLOT(callAdded(const QString&, const QMap<QString,QVariant>&)));

    /*bool callAddedAnswer = bus.connect("org.ofono", current_modem,
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
	    writeLog("CallAdded connection succeed", INFO);*/
    writeLog("Write log", INFO);

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
