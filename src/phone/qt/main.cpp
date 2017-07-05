#include <iostream>
#include <QDebug>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    if(argc < 2) {
        qDebug() << "To start dialerApp you need to specify sim-module for call making\nFormat: \\sim900_0";
        exit(1);
    }
    QApplication a(argc, argv);
    if(argc == 2) {
        MainWindow w;
        w.setSim(argv[1]);
        w.showDialer();
    }
    return a.exec();
}
