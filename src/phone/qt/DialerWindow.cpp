#include <QtWidgets/QTextEdit>
#include <QtWidgets/QPushButton>
#include <QScreen>
#include <QDebug>
#include <iostream>
#include <QtDBus/QDBusInterface>
#include "DialerWindow.h"
#include "Button.h"
#include "CallWindow.h"
#include "Additional.h"

DialerWindow::DialerWindow(QWidget *parent)
        : QWidget(parent)
{
    getSimPath();
    screenSize = getScreenSize();
    createCommonLayout();
}

DialerWindow::~DialerWindow(){

}

void DialerWindow::showDialer(){
    mainWindow = new QWidget();
    mainWindow ->setAutoFillBackground(true);
    mainWindow ->setPalette(getCommonPalette(this));
    mainWindow->setFixedSize(screenSize.width(), screenSize.height());
    mainWindow->activateWindow();
    mainWindow->setLayout(commonLayout);
    mainWindow->show();
}

void DialerWindow::dialNumber()
{
    QString dialedNumber = phoneNumber->text();
	if(dialedNumber.isEmpty() || dialedNumber.isNull())
		return;

    makeCall(dialedNumber);

    CallWindow *callWindow = new CallWindow(dialedNumber);
    callWindow->showWindow();
    mainWindow->close();
    delete(mainWindow);
    delete(this);
}

void DialerWindow::back(){
    exit(1);
}

void DialerWindow::erase(){
    if(phoneNumber->text().isEmpty())
        return;

    int size = phoneNumber->text().size() - 1;
    std::string newText = phoneNumber->text().toStdString().substr(0, size);
    phoneNumber->setText(newText.c_str());
}

void DialerWindow::createCommonLayout(){
    QGridLayout* textLayout = new QGridLayout();

    Button *back = new Button();
    back -> createButtonIco(get_icoPath("back.png"), QSize(170, 70));
    connect(back, SIGNAL(clicked()), this, SLOT(back()));

    Button *erase = new Button();
    erase->createButtonIco(get_icoPath("erase.png"), QSize(70, 70));
    connect(erase, SIGNAL(clicked()), this, SLOT(erase()));

    Button *dial = new Button();
    dial->createButtonIco(get_icoPath("dial.png"), QSize(70, 70));
    connect(dial, SIGNAL(clicked()), this, SLOT(dialNumber()));

    phoneNumber = new QLabel();
    QFont textFont = phoneNumber->font();
    textFont.setPointSize(20);
    textFont.setBold(true);
    phoneNumber->setFont(textFont);

    textLayout->addWidget(back, 0, 0, Qt::AlignLeft);
    textLayout->addWidget(erase, 0, 1, Qt::AlignRight);

    QWidget* buttonField = new QWidget();
    buttonField->setAutoFillBackground(true);
    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::black);
    buttonField->setPalette(pal);
    buttonField->setFixedSize(screenSize.width() - screenSize.width() * 0.07 * 2,
                              screenSize.height() / 2);

    Button *btn = new Button();
    btn->setLabel(phoneNumber);
    QGridLayout* buttonLayout = btn->createButtonGrid(buttonField);

    buttonField->setLayout(buttonLayout);

    commonLayout = new QGridLayout();
    commonLayout->setSpacing(5);
    commonLayout->addLayout(textLayout, 0, 0, Qt::AlignCenter);
    commonLayout->addWidget(phoneNumber, 1, 0, Qt::AlignCenter);
    commonLayout->addWidget(buttonField, 2, 0, Qt::AlignCenter);
    commonLayout->addWidget(dial, 3,0, Qt::AlignCenter);
}