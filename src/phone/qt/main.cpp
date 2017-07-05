#include <QDebug>
#include "DialerWindow.h"
#include "IncomingCall.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    if(argc < 2) {
        DialerWindow *w = new DialerWindow();
        w->showDialer();
    }else{
        IncomingCall *incoming = new IncomingCall(argv[1]);
        incoming->showIncoming();
    }

    return a.exec();
}
