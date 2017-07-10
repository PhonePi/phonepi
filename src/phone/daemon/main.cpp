#include <fstream>
#include "Additional.h"
#include "Modem.h"

#define INFO 0
#define ERROR -1

int main() {

    writeLog("-------------------", INFO);
    writeLog("Start calls daemon", INFO);
    DBus *dbus_class = new DBus;

    system("mkdir -p /usr/share/phonepi");
    system("rm -f /usr/share/phonepi/info");

    Modem current_modem(dbus_class, "/sim900_0");
    current_modem.enableModem();
    current_modem.getOperator();

    int pid = fork();
    if(pid == -1) {
        writeLog("Daemon launching failed.\n", ERROR);
        writeLog("-------------------", INFO);
        return -1;
    }
    else if(!pid){
            writeLog("Daemon lauched", INFO);
            umask(0);
            setsid();
            chdir("/");

            close(STDIN_FILENO);
            close(STDOUT_FILENO);
            close(STDERR_FILENO);

            return current_modem.getCalls();

    } else
        return 0;
}
