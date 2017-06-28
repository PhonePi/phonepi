#ifndef DAEMON_STRUCT_H
#define DAEMON_STRUCT_H

#include <vector>
#include <zconf.h>
#include <sys/stat.h>
#include <syslog.h>
#include <cstring>
#include <glib.h>

#define INFO 0
#define ERROR -1
#define ENDOFLOG writeLog("-------------------", INFO)

static struct g_prop{
    GString prop_name;
    GString prop_val;
} props;

static struct g_answer{
    GString name;
    std::vector<g_prop> props;
} answer;

static bool value = false;
static void writeLog(const char* message, int status) {
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

#endif
//DAEMON_STRUCT_H
