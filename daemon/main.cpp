#include <fstream>
#include <glib.h>
#include <dbus/dbus.h>
#include <dbus/dbus-glib-lowlevel.h>
#include "Additional.h"
#include "Modem.h"

#define INFO 0
#define ERROR -1

int callsMonitor();
void writeLog(const char*, int);
int setupHandler();
DBusHandlerResult call_added_callback(DBusConnection*, DBusMessage*, void *);
DBusConnection *connection;
DBusError error;

int main() {

    writeLog("Start calls daemon", INFO);
    connection = connectToBus(error);

    Modem current_modem(connection, "/sim900_0");
    current_modem.enableModem();
    current_modem.getOperator();

    int pid = fork();
    if(pid == -1) {
        writeLog("Daemon launching failed.\n", ERROR);
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

        //return callsMonitor();

    } else
        return 0;
}

DBusHandlerResult call_added_callback(DBusConnection *con, DBusMessage *msg, void *user_data){
    if(dbus_message_is_signal(msg, "org.ofono.VoiceCallManager", "CallAdded"))
        writeLog("CallAdded callback", INFO);

    if(dbus_message_is_signal(msg, "org.ofono.VoiceCallManager", "CallRemoved"))
        writeLog("CallRemoved callback", INFO);

    return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}

int setupHandler() {
    writeLog("Handler settings", INFO);
    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    dbus_connection_setup_with_g_main(connection, NULL);

    char *rule = "type='signal', interface='org.ofono.VoiceCallManager'";
    dbus_bus_add_match(connection, rule, &error);

    if(dbus_error_is_set(&error)){
        writeLog(strcat("Cannot add D-BUS match rule, cause: ", error.message), ERROR);
        dbus_error_free(&error);
        return EXIT_FAILURE;
    }

    writeLog("Listenning to D-BUS signals using a connection filter", INFO);
    dbus_connection_add_filter(connection, call_added_callback, NULL, NULL);

    g_main_loop_run(loop);

    return EXIT_SUCCESS;
}
