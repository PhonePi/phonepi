#include <QtWidgets/QTextEdit>
#include <QtWidgets/QPushButton>
#include <QScreen>
#include <QDebug>
#include <QtDBus/QDBusInterface>
#include "DialerWindow.h"
#include "Button.h"
#include "CallWindow.h"
#include "IncomingCall.h"

IncomingCall::IncomingCall(QString phoneNumber, QWidget *parent)
        : QWidget(parent)
{
    this->phoneNumber = phoneNumber;
    qDebug() << "Call from: " << this->phoneNumber;
    getScreenSize();
    createCommonLayout();
}

IncomingCall::~IncomingCall()
{}

void IncomingCall::showIncoming() {
    incomingWindow = new QWidget();
    incomingWindow ->setAutoFillBackground(true);
    QPalette pal(palette());
    pal.setColor(QPalette::Background, "#fbf1c7");
    incomingWindow ->setPalette(pal);
    incomingWindow->setFixedSize(screenSize.width(), screenSize.height());
    incomingWindow->activateWindow();
    incomingWindow->setLayout(commonLayout);
    incomingWindow->show();
}

void IncomingCall::hang(){
    qDebug() << "hang slot";
    DialerWindow dialerWindow;
    dialerWindow.showDialer();
    incomingWindow->close();
}

void IncomingCall::answer(){
    qDebug() << "answer slot";
    CallWindow callWindow(phoneNumber);
    callWindow.showWindow();
    incomingWindow->close();
}

void IncomingCall::getScreenSize() {
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    screenSize.setWidth(screenGeometry.width());
    screenSize.setHeight(screenGeometry.height());
}

void IncomingCall::createCommonLayout() {
    QLabel *incoming = new QLabel();
    QFont textFont = incoming->font();
    textFont.setPointSize(30);
    textFont.setBold(true);
    incoming->setFont(textFont);
    incoming->setText("Incoming from:");

    QLabel *phoneNumber = new QLabel();
    textFont = phoneNumber->font();
    textFont.setPointSize(30);
    textFont.setBold(true);
    phoneNumber->setFont(textFont);
    phoneNumber->setText(this->phoneNumber);

    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->setContentsMargins(screenSize.width()/10, screenSize.height()/10, screenSize.width()/10, screenSize.width()/10);
    gridLayout->addWidget(incoming, 0, 0, Qt::AlignLeft);
    gridLayout->addWidget(phoneNumber, 1, 0, Qt::AlignLeft);

    Button *dial = new Button();
    dial->createButtonIco(workingDir + "pics//dial.png", QSize(70, 70));
    connect(dial, SIGNAL(clicked()), this, SLOT(answer()));

    Button *hang = new Button();
    hang->createButtonIco(workingDir + "pics//hang.png", QSize(120, 50));
    connect(hang, SIGNAL(clicked()), this, SLOT(hang()));

    commonLayout = new QGridLayout();
    commonLayout->setSpacing(5);
    commonLayout->setContentsMargins(screenSize.width()/10, screenSize.height()/10, screenSize.width()/10, screenSize.width()/10);
    commonLayout->addLayout(gridLayout, 1, 1, Qt::AlignCenter | Qt::AlignTop);
    commonLayout->addWidget(dial, 2, 0, Qt::AlignRight | Qt::AlignBottom);
    commonLayout->addWidget(hang, 2, 2, Qt::AlignLeft | Qt::AlignBottom);
}