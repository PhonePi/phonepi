#include <iostream>
#include <QDebug>
#include "DialerWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    DialerWindow w;
    w.showDialer();

    return a.exec();
}
