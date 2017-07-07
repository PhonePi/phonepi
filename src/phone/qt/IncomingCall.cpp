#include <QTextEdit>
#include <QScreen>
#include <QtDBus/QDBusInterface>
#include <csignal>
#include <iostream>
#include "DialerWindow.h"
#include "Button.h"
#include "CallWindow.h"
#include "IncomingCall.h"
#include "Additional.h"

IncomingCall::IncomingCall(QString callPath, QString phoneNumber, QWidget *parent)
        : QWidget(parent)
{
    this->callPath = callPath;
    this->phoneNumber = phoneNumber;
    screenSize = getScreenSize();
    createCommonLayout();

    std::signal(SIGUSR1, signalHandler);
}

IncomingCall::~IncomingCall() {
}

void IncomingCall::showIncoming() {
    incomingWindow = new QWidget();
    incomingWindow ->setAutoFillBackground(true);
    incomingWindow ->setPalette(getCommonPalette(this));
    incomingWindow->setFixedSize(screenSize.width(), screenSize.height());
    incomingWindow->activateWindow();
    incomingWindow->setLayout(commonLayout);
    incomingWindow->show();

    setWidgetInfo(incomingWindow, this);
}

void IncomingCall::hang(){
    hangUp();
}

void IncomingCall::answer() {
    answerCall(callPath);

    CallWindow *callWindow = new CallWindow(phoneNumber);
    callWindow->showWindow();
    incomingWindow->close();
    delete (incomingWindow);
    delete (this);
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
    gridLayout->setContentsMargins(screenSize.width()/10, screenSize.height()/10,
                                   screenSize.width()/10, screenSize.width()/10);
    gridLayout->addWidget(incoming, 0, 0, Qt::AlignLeft);
    gridLayout->addWidget(phoneNumber, 1, 0, Qt::AlignLeft);

    Button *dial = new Button();
    dial->createButtonIco(get_icoPath("answer.png"), QSize(90, 120));
    connect(dial, SIGNAL(clicked()), this, SLOT(answer()));

    Button *hang = new Button();
    hang->createButtonIco(get_icoPath("hang.png"), QSize(150, 60));
    connect(hang, SIGNAL(clicked()), this, SLOT(hang()));

    commonLayout = new QGridLayout();
    commonLayout->setSpacing(5);
    commonLayout->setContentsMargins(screenSize.width()/10, screenSize.height()/10,
                                     screenSize.width()/10, screenSize.width()/10);
    commonLayout->addLayout(gridLayout, 1, 1, Qt::AlignCenter | Qt::AlignTop);
    commonLayout->addWidget(dial, 2, 0, Qt::AlignRight | Qt::AlignBottom);
    commonLayout->addWidget(hang, 2, 2, Qt::AlignLeft | Qt::AlignBottom);
}