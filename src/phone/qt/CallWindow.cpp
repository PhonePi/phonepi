#include <QtGui/QGuiApplication>
#include "CallWindow.h"
#include "Button.h"
#include "DialerWindow.h"
#include <QScreen>
#include <QDebug>
#include <QTimer>

CallWindow::CallWindow(QString phoneNumber, QWidget *parent)
        : QWidget(parent)
{
    this->phoneNumber = phoneNumber;
    secs = 0;
    min = 0;
    getScreenSize();
    createCommonLayout();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimerLabel()));
    timer->start(1000);
}

CallWindow::~CallWindow() {}

void CallWindow::getScreenSize() {
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    screenSize.setWidth(screenGeometry.width());
    screenSize.setHeight(screenGeometry.height());
}

void CallWindow::createCommonLayout() {
    QWidget* callerWidget = new QWidget();
    callerWidget->setAutoFillBackground(true);
    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::blue);
    callerWidget->setPalette(pal);
    callerWidget->setFixedSize(screenSize.width(), screenSize.height() / 2);
    callerWidget->setContentsMargins(screenSize.width()/10, 0, screenSize.width()/10,  0);

    std::string fontColor = "QLabel { color: white; }";

    QLabel *callText = new QLabel();
    callText->setStyleSheet(QString(fontColor.c_str()));
    QFont textFont = callText->font();
    textFont.setPointSize(30);
    textFont.setBold(true);
    callText->setFont(textFont);
    callText->setText("Call with:");

    QLabel *phoneNumber = new QLabel();
    phoneNumber->setStyleSheet(QString(fontColor.c_str()));
    textFont = phoneNumber->font();
    textFont.setPointSize(30);
    textFont.setBold(true);
    phoneNumber->setFont(textFont);
    phoneNumber->setText(this->phoneNumber);

    timerLabel = new QLabel();
    timerLabel->setStyleSheet(QString(fontColor.c_str()));
    textFont = timerLabel->font();
    textFont.setPointSize(30);
    textFont.setBold(true);
    timerLabel->setFont(textFont);
    timerLabel->setText("00:00");

    QGridLayout *callerLayout = new QGridLayout();
    callerLayout->setSpacing(0);

    callerLayout->addWidget(callText, 1,1, Qt::AlignLeft);
    callerLayout->addWidget(timerLabel, 1,2, Qt::AlignRight);
    callerLayout->addWidget(phoneNumber, 2,1, Qt::AlignLeft);

    callerWidget->setLayout(callerLayout);

    std::string workingDir = "//home//arseny//Repos//KSPT//Phone//src//phone//qt//";
    Button *hang = new Button();
    hang->createButtonIco(workingDir + "pics//hang.png", QSize(100,50));
    connect(hang, SIGNAL(clicked()), this, SLOT(hang()));

    commonLayout = new QGridLayout();
    commonLayout->setSpacing(5);
    commonLayout->addWidget(callerWidget, 1, 1, Qt::AlignCenter | Qt::AlignTop);
    commonLayout->addWidget(hang, 3, 1, Qt::AlignCenter | Qt::AlignBottom);
}

void CallWindow::showWindow() {
    callWindow = new QWidget();
    callWindow->setAutoFillBackground(true);
    QPalette pal(palette());
    pal.setColor(QPalette::Background, "#fbf1c7");
    callWindow->setPalette(pal);
    callWindow->setFixedSize(screenSize.width(), screenSize.height());
    callWindow->activateWindow();
    callWindow->setLayout(commonLayout);
    callWindow->show();
}

void CallWindow::updateTimerLabel() {
    qDebug() << "updateLabel";
    secs++;
    if(secs > 59) {
        min++;
        secs = 0;
    }

    if(secs < 10)
        timerLabel->setText(min + ":0" + secs);
    else
        timerLabel->setText(min + ":" + secs);
}

void CallWindow::hang() {
    qDebug() << "hang slot";
    DialerWindow dialerWindow;
    dialerWindow.showDialer();
    callWindow->close();
}