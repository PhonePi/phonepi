#include <QtGui/QGuiApplication>
#include "CallWindow.h"
#include "Button.h"
#include "DialerWindow.h"
#include "Additional.h"
#include <QTimer>

CallWindow::CallWindow(QString phoneNumber, QWidget *parent)
        : QWidget(parent)
{
    this->phoneNumber = phoneNumber;
    secs = 0;
    min = 0;
    screenSize = getScreenSize();
    createCommonLayout();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimerLabel()));
    timer->start(1000);
}

CallWindow::~CallWindow() {
}

void CallWindow::createCommonLayout() {
    QLabel *callText = new QLabel();
    QFont textFont = callText->font();
    textFont.setPointSize(30);
    textFont.setBold(true);
    callText->setFont(textFont);
    callText->setText("Call with:");

    QLabel *phoneNumber = new QLabel();
    textFont = phoneNumber->font();
    textFont.setPointSize(30);
    textFont.setBold(true);
    phoneNumber->setFont(textFont);
    phoneNumber->setText(this->phoneNumber);

    timerLabel = new QLabel();
    textFont = timerLabel->font();
    textFont.setPointSize(30);
    textFont.setBold(true);
    timerLabel->setFont(textFont);
    timerLabel->setText("0:00");

    QGridLayout *callerLayout = new QGridLayout();
    callerLayout->setSpacing(5);
    callerLayout->setContentsMargins(screenSize.width()/20, screenSize.height()/10, screenSize.width()/20, screenSize.width()/10);

    callerLayout->addWidget(callText, 1,1, Qt::AlignLeft);
    callerLayout->addWidget(phoneNumber, 1,2, Qt::AlignRight);
    callerLayout->addWidget(timerLabel, 2,2, Qt::AlignRight);

    Button *hang = new Button();
    hang->createButtonIco(get_icoPath("hang.png"), QSize(100,50));
    connect(hang, SIGNAL(clicked()), this, SLOT(hang()));

    commonLayout = new QGridLayout();
    commonLayout->setSpacing(5);
    commonLayout->addLayout(callerLayout, 1, 0, Qt::AlignCenter | Qt::AlignTop);
    commonLayout->addWidget(hang, 2, 0, Qt::AlignCenter | Qt::AlignBottom);
}

void CallWindow::showWindow() {
    callWindow = new QWidget();
    callWindow->setAutoFillBackground(true);
    callWindow->setPalette(getCommonPalette(this));
    callWindow->setFixedSize(screenSize.width(), screenSize.height());
    callWindow->activateWindow();
    callWindow->setLayout(commonLayout);
    callWindow->show();
    elapsedTime.start();
}

void CallWindow::updateTimerLabel() {
    secs = elapsedTime.elapsed() / 1000;

    if(secs > 59){
        min = secs / 60;
        secs = secs - min * 60;
    }

    if(secs < 10) {
        std::string msg = std::to_string(min) + ":0" + std::to_string(secs);
        timerLabel->setText(msg.c_str());
    }
    else {
        std::string msg = std::to_string(min) + ":" + std::to_string(secs);
        timerLabel->setText(msg.c_str());
    }
}

void CallWindow::hang() {
    hangUp();

    DialerWindow *dialerWindow = new DialerWindow();
    dialerWindow->showDialer();
    callWindow->close();
    delete(callWindow);
    delete(this);
}
