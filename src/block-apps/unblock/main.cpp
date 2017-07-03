//
// Created by abdullin on 6/30/17.
//

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>

#include <iostream>
#include <thread>

#include "Config.h"
#include "UnblockExecutor.h"
#include "Timer.h"

int main(int argc, char** argv) {
    QApplication a(argc, argv);

    Config config;
    Timer timer;
    UnblockExecutor executor(&config);

    // start detached timer thread, that updates time label
    std::thread thread([&timer] () -> void {timer.start();});
    thread.detach();

    QWidget widget;
    QPalette Pal;

    std::string background = "background-image: url(" + config.getBackgroung() + ")";
    widget.setStyleSheet(QString(background.c_str()));

    // create time label
    QVBoxLayout* layout = new QVBoxLayout();
    QLabel* label = new QLabel();
    label->setText(getCurrentTime().c_str());
    std::string lblcolor = "QLabel { color : " + config.getFontColor() + "; }";
    label->setStyleSheet(QString(lblcolor.c_str()));
    QFont lblfont = label->font();
    lblfont.setPointSize(config.getFontSize());
    lblfont.setBold(true);
    label->setFont(lblfont);
    layout->addWidget(label, 0, Qt::AlignCenter);
    label->setAlignment(Qt::AlignCenter);
    QObject::connect(&timer, &Timer::updateTime, label, &QLabel::setText);

    // create unblock button
    QPushButton* button = new QPushButton();
    button->setText("Unblock");
    std::string btncolor = "QPushButton { color : " + config.getFontColor() + "; }";
    button->setStyleSheet(QString(btncolor.c_str()));
    QFont btnfont = button->font();
    btnfont.setPointSize(config.getFontSize());
    btnfont.setBold(true);
    button->setFont(btnfont);
    QObject::connect(button, &QPushButton::clicked, &executor, &UnblockExecutor::execute);
    layout->addWidget(button, 0, Qt::AlignCenter);

    // start application
    widget.setLayout(layout);
    widget.showFullScreen();
    widget.activateWindow();

    return a.exec();
}