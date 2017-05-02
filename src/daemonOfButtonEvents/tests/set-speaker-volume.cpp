#include <iostream>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <errno.h>

// QT
#include <QtCore/QStringList>
#include <QtDBus/QtDBus>

using namespace std;

int getDBusPath(QString &path);

int main(int argc, char *argv[]) {
	if (argc != 2){
		cout << "Bad argument!" << endl;
		exit(-1);
	}
	QString dBusPath;

	// get dbus path
	if (getDBusPath(dBusPath) !=0) {
		cout << "Sound Daemon Error#3: errno=" << errno << "; " <<  "Invalid DBus path;" << endl;
		exit(-1);
	}

	QDBusConnection bus = QDBusConnection::systemBus();
    if(!bus.isConnected()){
        qDebug() << "Invalid connectnion#12" << endl;
        exit(-101);
    }
	QDBusInterface cv("org.ofono", dBusPath, "org.ofono.CallVolume", bus);

	cv.call("SpeakerVolume", (unsigned char)atoi(argv[1]));
}


int getDBusPath(QString &path) {
		cout << "test1" << endl;
    QDBusConnection bus = QDBusConnection::systemBus();
    if(!bus.isConnected()){
        qDebug() << "Invalid connectnion#1" << endl;//.value();
        return -1;
    }
		cout << "test2" << endl;

    // default path
    QDBusInterface dbus_iface("org.ofono", "/", "org.ofono.Manager", bus);
    QDBusMessage modem = dbus_iface.call("GetModems");

    if(!modem.errorMessage().isNull() || !modem.errorMessage().isEmpty())
        return -2;

    QList<QVariant> outArgs = modem.arguments();
    const QDBusArgument &dbusArgs = outArgs.at(0).value<QDBusArgument>();

    dbusArgs.beginArray();
    while (!dbusArgs.atEnd()) {
        dbusArgs.beginStructure();
        while (!dbusArgs.atEnd()) {
            dbusArgs >> path;
            break;
            sleep(1);
        }
        dbusArgs.endStructure();
        break;
    }
    dbusArgs.endArray();

    return 0;
}
