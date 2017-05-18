/*
    КОСТЫЛИ. КОСТЫЛИ ВЕЗДЕ

    Реализованы следующие методы:
    Получение модема (Костыли. Нужна правильная обработка ответа)
    Подключение модема (дождаться ответа. Не открывать GUI без ответа)
    Звонок (После нажатия на кнопку перерисовать на совершение звонка. Дождаться ответа. После ответа добавление таймера вызова)
*/

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
	
//    GetModem();
//    EnableModem();
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

void MainWindow::GetModem()
{
    QDBusInterface dbus_iface("org.ofono", "/", "org.ofono.Manager", bus);

    QDBusMessage modem = dbus_iface.call("GetModems");

    AnswerValidation(modem);

    //qDebug() << modem;

    const QDBusArgument &dbusArgs = modem.arguments().first().value<QDBusArgument>();

    if (dbusArgs.currentType() != QDBusArgument::ArrayType)
    {
        qDebug() << "Not array";
        exit(1);
    }

    auto answer = getStructAnswer(dbusArgs);

    if(answer.size() == 0){
        qDebug() << "Answer is NULL";
        exit(1);
    }


    if(answer.size() == 1) {
        selected_modem = answer[0].name;
        isModemEnabled = answer[0].porp_map["Powered"];
        qDebug() << "Modem powered: " + isModemEnabled.toString().toLatin1();
    }else
        for(Answer_struct modem : answer)
            if(modem.name.contains("sim900")){
                selected_modem = modem.name;
                isModemEnabled = modem.porp_map["Powered"].toBool();
                qDebug() << "Modem powered: " + isModemEnabled.toString().toLatin1();
            }


    if(selected_modem.isNull() || selected_modem.isEmpty()) {
        qDebug() << "No modem was selected";
        exit(1);
    }else
        qDebug() << "Selected modem: " << selected_modem;
}


void MainWindow::EnableModem()
{
    if(selected_modem.isNull() || selected_modem.isEmpty())
    {
        qDebug() << "No modem to enable";
        exit(1);
    }

    QDBusInterface dbus_iface("org.ofono", selected_modem, "org.ofono.Modem", bus);

    QDBusMessage modem_status = dbus_iface.call("SetProperty",
                                                QString("Powered"), QVariant::fromValue(QDBusVariant(true)));

    AnswerValidation(modem_status);

    qDebug() << modem_status;

}

void MainWindow::DialNumber(QString call_number)
{
	if(call_number.isEmpty() || call_number.isNull())
		return;

	dialedNumber = call_number;
	QQmlEngine engine;
	engine.rootContext()->setContextProperty("window", this);
	QQmlComponent component(&engine);
	component.loadUrl(QUrl("qrc:///qml/dialing.qml"));
//	component.setProperty("call_numberText", call_number);
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
    QDBusMessage call_status = dbus_iface.callWithArgumentList(QDBus::BlockWithGui,
"Dial", args);    
	AnswerValidation(call_status);

    qDebug() << call_status;
}

QString MainWindow::GetNumber(){
	return dialedNumber;
}
