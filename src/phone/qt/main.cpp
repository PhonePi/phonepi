#include <QDebug>
#include "DialerWindow.h"
#include "IncomingCall.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    if(argc == 1) {
        DialerWindow *w = new DialerWindow();
        w->showDialer();
    }else if(argc == 3){
        IncomingCall *incoming = new IncomingCall(argv[1], argv[2]);
        incoming->showIncoming();
    }else{
        qDebug() << "ERROR: Incorrect use of dialer-pi.";
        qDebug() << "For dial number no arguments requred";
        qDebug() << "For answer call required: incoming call path and incoming number";
        qDebug() << "Format: ./dialer-pi <path> <number>";
        exit(1);
    }


    return a.exec();
}
