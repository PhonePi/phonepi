//
// Created by abdullin on 6/30/17.
//

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QSlider>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>

#include <iostream>
#include <QtWidgets/QPushButton>


int main(int argc, char** argv) {
    QApplication a(argc, argv);
    QWidget widget;
    QPalette Pal;

    // setting background color
    Pal.setColor(QPalette::Background, Qt::black);
    widget.setAutoFillBackground(true);
    widget.setPalette(Pal);


    // start application
    widget.showFullScreen();
    widget.activateWindow();

    return a.exec();
}