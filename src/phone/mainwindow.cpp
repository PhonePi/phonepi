
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

	QDBusConnection bus = QDBusConnection::systemBus();
	
	if(!bus.isConnected())
		fprintf(stderr, "Couldn't connect");

	QDBusInterface dbus_iface("org.ofono", "/", "org.ofono.Manager", bus);

	QDBusMessage modem = dbus_iface.call("GetModems");

	if(QDBusMessage::ErrorMessage == modem.type()){
		qDebug() << modem.errorMessage();
		return;
	}
	
	qDebug() << modem;
	qDebug() << modem.arguments();

	/*const QDBusArgument &dbusArgs = */qDebug() << modem.arguments().first();//.value<QDBusArgument>();

	//qDebug() << dbusArgs;

	//QDBusObjectPath path;
	//qDebug() << dbusArgs.currentType();
    /*dbusArgs.beginArray();
    while (!dbusArgs.atEnd())
    {
        dbusArgs >> path;
    }
    dbusArgs.endArray();*/
    //dbusArgs >> path;
    //qDebug() << path.path();
}