#include <iostream>
#include <QString>
#include <QtDBus>
#include <zconf.h>
#include <sys/stat.h>
#include <syslog.h>

#define INFO 0
#define ERROR -1

typedef struct{
    QString name;
    QMap<QString, QVariant> porp_map;
} Answer_struct;
Q_DECLARE_METATYPE(Answer_struct)

bool isAnswerValid(QDBusMessage);
int callsMonitor(QDBusConnection, QString);
std::vector<Answer_struct> getStructAnswer(const QDBusArgument&);
void writeLog(const char*, int);

int main() {

    QDBusConnection bus = QDBusConnection::systemBus();

    if(!bus.isConnected())
        exit(1);

    QDBusInterface dbus_iface("org.ofono", "/", "org.ofono.Manager", bus);
    QDBusMessage modem = dbus_iface.call("GetModems");

    if(!isAnswerValid(modem))
        exit(1);

    const QDBusArgument &dbusArgs = modem.arguments().first().value<QDBusArgument>();
    std::vector<Answer_struct> answers = getStructAnswer(dbusArgs);
    QString selected_modem;

    if(answers.size() == 1)
        selected_modem = answers[0].name;
    else
        for(Answer_struct modem : answers)
            if(modem.name.contains("sim900"))
                selected_modem = modem.name;

    if(selected_modem.isNull() || selected_modem.isEmpty()) {
        writeLog("No modem was selected", ERROR);
        exit(1);
    }

    writeLog(strcat("Selected modem: ", selected_modem.toStdString().c_str()), INFO);
    QDBusInterface enable_iface("org.ofono", selected_modem, "org.ofono.Modem", bus);
    QDBusMessage modem_status = dbus_iface.call("SetProperty", QString("Powered"),
                                                QVariant::fromValue(QDBusVariant("true")));

    if(isAnswerValid(modem_status))
        exit(1);

    writeLog("Modem succesffuly enabled", INFO);

    int pid = fork();
    if(pid == -1) {
        writeLog("Daemon launching failed.\n", ERROR);
        return -1;
    }
    else if(!pid){
        umask(0);
        setsid();
        chdir("/");

        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);

        return callsMonitor(bus, selected_modem);

    } else
        return 0;
}

bool isAnswerValid(QDBusMessage msg) {
    if(QDBusMessage::ErrorMessage == msg.type()){
        writeLog(msg.errorMessage().toStdString().c_str(), ERROR);
        return false;
    }
    return true;
}

std::vector<Answer_struct> getStructAnswer(const QDBusArgument &dbusArgs) {
    QString selected_modem;
    Answer_struct answer_struct;
    std::vector<Answer_struct> answers;
    dbusArgs.beginArray();
    while (!dbusArgs.atEnd()) {
        dbusArgs.beginStructure();
        if (dbusArgs.currentType() == 0)
            dbusArgs >> answer_struct.name;
        if (dbusArgs.currentType() == 4)
            dbusArgs >> answer_struct.porp_map;
        dbusArgs.endStructure();
        answers.push_back(answer_struct);
    }
    dbusArgs.endArray();

    return answers;
}

int callsMonitor(QDBusConnection bus, QString current_modem){
    if(!bus.isConnected())
        exit(1);

    QDBusInterface dbus_iface("org.ofono", current_modem, "org.ofono.VoiceCallManager", bus);
    QDBusMessage calls = dbus_iface.call("GetCalls");

    if(!isAnswerValid(calls)){
        exit(1);
    }



}

void writeLog(const char* message, int status) {
    openlog("calls_daemon", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);

    switch(status){
        case ERROR:
            syslog(LOG_ERR, message);
            break;
        case INFO:
            syslog(LOG_INFO, message);
            break;
        default:
            syslog(LOG_ALERT, message);
            break;
    }

    closelog();
}