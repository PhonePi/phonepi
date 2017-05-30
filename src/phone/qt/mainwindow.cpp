#include "mainwindow.h"
#include <QQmlComponent>
#include <QQuickItem>

MainWindow::MainWindow(QObject *parent)
    : QQmlApplicationEngine(parent)
{
	load(QUrl("qrc:///qml/main.qml"));
	rootContext()->setContextProperty("window", this);
	if(!bus.isConnected())
		exit(1);
}

MainWindow::~MainWindow()
{

}

std::vector<Answer_struct> getStructAnswer(const QDBusArgument &dbusArgs) {
    QString selected_modem;
    Answer_struct answer_struct;
    std::vector<Answer_struct> answers;
    dbusArgs.beginArray();
    while (!dbusArgs.atEnd()) {
        dbusArgs.beginStructure();
        if (dbusArgs.currentType() == 0)
            dbusArgs >> answer_struct.name;
        if (dbusArgs.currentType() == 4)
            dbusArgs >> answer_struct.porp_map;
        dbusArgs.endStructure();
        answers.push_back(answer_struct);
    }
    dbusArgs.endArray();

    return answers;
}

void MainWindow::AnswerValidation(QDBusMessage msg)
{
    if(QDBusMessage::ErrorMessage == msg.type()){
        qDebug() << msg.errorMessage();
        exit(1);
    }
}

void MainWindow::dialNumber(QString call_number)
{
	if(call_number.isEmpty() || call_number.isNull())
		return;

	dialedNumber = call_number;
	QQmlEngine engine;
	engine.rootContext()->setContextProperty("window", this);
	QQmlComponent component(&engine);
	component.loadUrl(QUrl("qrc:///qml/dialing.qml"));
	QObject *text = component.findChild<QObject*>("call_number");
	if(text) {
		qDebug() << "Setting prop"; 
		text -> setProperty("text", call_number);
	}

	if ( component.isReady() ){
	    component.create();
	}
	else
	    qWarning() << component.errorString();


    QVariant number(QVariant::String);
	number = call_number;
    QList<QVariant>args;
    QDBusInterface dbus_iface("org.ofono", selected_modem, "org.ofono.VoiceCallManager", bus);
    args.append(number);
    args.append("");
    QDBusMessage call_status = dbus_iface.callWithArgumentList(QDBus::BlockWithGui, "Dial", args);
	AnswerValidation(call_status);

    qDebug() << call_status;
}
