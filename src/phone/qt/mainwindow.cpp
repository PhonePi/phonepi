#include <QtWidgets/QTextEdit>
#include <QtWidgets/QPushButton>
#include <QScreen>
#include <QDebug>
#include <iostream>
#include <sys/stat.h>
#include "mainwindow.h"
#include "Button.h"

MainWindow::MainWindow(QWidget *parent)
        : QWidget(parent)
{
    getSimPath();
    qDebug() << "Using modem: " << selected_modem;
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    width = screenGeometry.width();
    height = screenGeometry.height();

    textField = new QWidget();
    textLayout = new QGridLayout();

    Button *back = new Button();
    back -> createButtonIco(workingDir + "pics//back.png", QSize(170, 70));
    connect(back, SIGNAL(clicked()), this, SLOT(back()));

    Button *erase = new Button();
    erase->createButtonIco(workingDir + "pics//erase.png", QSize(70, 70));
    connect(erase, SIGNAL(clicked()), this, SLOT(erase()));

    Button *dial = new Button();
    dial->createButtonIco(workingDir + "pics//dial.png", QSize(70, 70));
    connect(dial, SIGNAL(clicked()), this, SLOT(dialNumber()));

    phoneNumber = new QLabel();
    QFont textFont = phoneNumber->font();
    textFont.setPointSize(20);
    textFont.setBold(true);
    phoneNumber->setFont(textFont);

    textLayout->addWidget(back, 0, 0, Qt::AlignRight);
    textLayout->addWidget(erase, 0, 2, Qt::AlignLeft);


    buttonField = new QWidget();
    buttonField->setAutoFillBackground(true);
    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::black);
    buttonField->setPalette(pal);
    buttonField->setFixedSize(width - width * 0.07 * 2, height/2);

    Button *btn = new Button();
    btn->setLabel(phoneNumber);
    buttonLayout = btn->createButtonGrid(buttonField);

    buttonField->setLayout(buttonLayout);

    commonLayout = new QGridLayout();
    commonLayout->setSpacing(5);
    commonLayout->addLayout(textLayout, 0, 0, Qt::AlignCenter);
    commonLayout->addWidget(phoneNumber, 1, 0, Qt::AlignCenter);
    commonLayout->addWidget(buttonField, 2, 0, Qt::AlignCenter);
    commonLayout->addWidget(dial, 3,0, Qt::AlignCenter);
}

MainWindow::~MainWindow()
{}

void MainWindow::showDialer(){
    mainWindow = new QWidget();

    mainWindow ->setAutoFillBackground(true);
    QPalette pal(palette());
    pal.setColor(QPalette::Background, "#fbf1c7");
    mainWindow ->setPalette(pal);

    mainWindow->setLayout(commonLayout);

    mainWindow->setFixedSize(width, height);
    mainWindow->activateWindow();
    mainWindow->show();
}

void MainWindow::dialNumber()
{
    dialedNumber = phoneNumber->text();
	if(dialedNumber.isEmpty() || dialedNumber.isNull())
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

void MainWindow::getSimPath(){
    struct stat buf;
    if(stat("//home//arseny//.modem", &buf) != 0){
        qDebug() << "Cannot find file ~/.modem";
        qDebug() << "For correct work of dialer app sim-module is required";
        exit(1);
    }

    FILE *fp;
    char buffer[20];
    fp = popen("cat ~//.modem", "r");
    if (fp != NULL)
    {
        while (fgets(buffer, sizeof(buffer), fp) != NULL)
        pclose(fp);
    }
    selected_modem = buffer;
}