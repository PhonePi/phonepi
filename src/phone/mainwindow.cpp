
#include "mainwindow.h"
#include <QString>
#include <QtDBus/QtDBus>
#include <QDBusConnection>
#include <QDBusMessage>

MainWindow::MainWindow(QObject *parent)
    : QQmlApplicationEngine(parent)
{
	//setFocusPolicy(Qt::StrongFocus);
	//setResizeMode(QDeclarativeView::SizeRootObjectToView);
	//setSource(QUrl("qrc:///main.qml"));
	//rootContext()->setContextProperty("window", this);
	load(QUrl("qrc:///main.qml"));
	rootContext()->setContextProperty("window", this);
}

MainWindow::~MainWindow()
{

}

void MainWindow::EmptyFunc()
{
	QApplication::quit();
}

void MainWindow::DialNumber(QString number)
{
	if(number.isEmpty() || number.isNull())
		return;

	QDBusConnection bus = QDBusConnection::sessionBus();
	
	if(!bus.isConnected())
		fprintf(stderr, "Couldn't connect");

	QDBusInterface dbus_iface("org.ofono", "/", 
							"org.ofono.Manager", bus);
	qDebug() << dbus_iface.service();
	qDebug() << dbus_iface.path();
	qDebug() << dbus_iface.interface();

	auto modem = dbus_iface.call("GetModems");

	qDebug() << modem;

	for( auto &&i : modem.arguments())
	{
		qDebug() << "Modem: " << i.toString();
	}
}