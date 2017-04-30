/*
    КОСТЫЛИ. КОСТЫЛИ ВЕЗДЕ

    Реализованы следующие методы:
    Получение модема (Костыли. Нужна правильная обработка ответа)
    Подключение модема (дождаться ответа. Не открывать GUI без ответа)
    Звонок (После нажатия на кнопку перерисовать на совершение звонка. Дождаться ответа. После ответа добавление таймера вызова)
*/

#include "mainwindow.h"

MainWindow::MainWindow(QObject *parent)
    : QQmlApplicationEngine(parent)
{
	load(QUrl("qrc:///qml/main.qml"));
	rootContext()->setContextProperty("window", this);
    //GetModem();
    //EnableModem();
}

MainWindow::~MainWindow()
{

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
    if(!bus.isConnected())
        exit(1);

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

    dbusArgs.beginArray();
    while (!dbusArgs.atEnd())
    {
        dbusArgs.beginStructure();
        dbusArgs >> selected_modem;
        dbusArgs.endStructure();

        //if(selected_modem.contains("sim900"))
            break;
    }
    dbusArgs.endArray();

    qDebug() << "Selected modem: " << selected_modem;
}


void MainWindow::EnableModem()
{
    if(!bus.isConnected())
        exit(1);

    if(selected_modem.isNull() || selected_modem.isEmpty())
    {
        qDebug() << "No modem to enable";
        exit(1);
    }

    QDBusInterface dbus_iface("org.ofono", selected_modem, "org.ofono.Modem", bus);

    QDBusMessage modem_status = dbus_iface.call("SetProperty", QString("Powered"), QVariant::fromValue(QDBusVariant(true)));

    AnswerValidation(modem_status);

    qDebug() << modem_status;

}

void MainWindow::DialNumber(QString number)
{
	if(number.isEmpty() || number.isNull())
		return;

	load(QUrl("qrc:///dialing.qml"));

    /*if(!bus.isConnected())
        exit(1);

    QDBusInterface dbus_iface("org.ofono", selected_modem, "org.ofono.VoiceCallManager", bus);

    QDBusMessage call_status = dbus_iface.call("Dial", number, QString("default"));

    AnswerValidation(call_status);

    qDebug() << call_status;*/

}