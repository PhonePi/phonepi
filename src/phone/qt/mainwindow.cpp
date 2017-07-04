#include <QtWidgets/QTextEdit>
#include <QtWidgets/QPushButton>
#include "mainwindow.h"
#include "Button.h"

MainWindow::MainWindow(QWidget *parent)
        : QWidget(parent)
{

    textField = new QWidget();
    textLayout = new QGridLayout();

    Button btn;
    QPushButton *backButton = btn.createButtonIco("pics//back.png", QSize(170, 70));
    connect(backButton, SIGNAL(clicked()), this, SLOT(back()));

    QPushButton *erase = btn.createButtonIco("pics//erase.png", QSize(70, 70));
    connect(erase, SIGNAL(clicked()), this, SLOT(erase()));

    phoneNumber = new QLabel();
    QFont textFont = phoneNumber->font();
    textFont.setPointSize(30);
    textFont.setBold(true);
    phoneNumber->setFont(textFont);

    textLayout->addWidget(backButton, 0, 0, Qt::AlignRight);
    textLayout->addWidget(phoneNumber, 0, 1, Qt::AlignCenter);
    textLayout->addWidget(erase, 0, 2, Qt::AlignLeft);


}

MainWindow::~MainWindow()
{

}

void MainWindow::dialNumber(QString call_number)
{
	if(call_number.isEmpty() || call_number.isNull())
		return;

    //load(QUrl("qrc:///qml/dialing.qml"));

    //QList<QObject*> objectList = this->rootObjects();
    //QObject* object =  objectList[1]->findChild<QObject*>("call_number");
    //if(object)
    //    object->setProperty("text", call_number);

    //qDebug() << call_number;
    //QDBusInterface dbus_iface("org.ofono", selected_modem, "org.ofono.VoiceCallManager", bus);
    //dbus_iface.call(QDBus::Block, "Dial", QVariant::fromValue(QString(call_number)), QVariant::fromValue(QString("")));

}

void MainWindow::back(){
    exit(1);
}

void MainWindow::erase(){
    if(phoneNumber->text().isEmpty())
        return;

    int size = phoneNumber->text().size() - 1;
    std::string newText = phoneNumber->text().toStdString().substr(0, size);
    phoneNumber->setText(newText.c_str());
}