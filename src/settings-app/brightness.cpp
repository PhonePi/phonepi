//
// Created by kivi on 31.05.17.
//

#include <sys/socket.h>
#include <sys/un.h>

#include <cstdio>
#include <pthread.h>
#include <unistd.h>

#include "brightness.h"

const char I2C_CMD_BRIGTH = 0xDD;   // "Set display brightness" (async.)
const char *socket_path = "hidden";
char brightnessValue = 100;

void startUpBrightnessThread() {
    pthread_t      tid;  // thread ID
    pthread_attr_t attr; // thread attribute

    // set thread detachstate attribute to DETACHED
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    // create the thread
    pthread_create(&tid, &attr, brightnessThread, NULL);
}

void readBrightness(int newVal) {
    brightnessValue = (char) newVal;
}

void* brightnessThread(void*) {
    char oldBrightness = 0;
    while (true) {
        if (brightnessValue != oldBrightness) {
            if (brightnessValue != 0) {
                oldBrightness = brightnessValue;
                setBrightness(brightnessValue);
            }
        }
        usleep(250000);
    }
}

void setBrightness(char val) {
    struct sockaddr_un addr;
    char buf[100];
    int fd;

    if ( (fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket error");
    }

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);

    if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("connect error");
    }

    buf[0] = I2C_CMD_BRIGTH;
    buf[1] = val;
    if (write(fd, buf, 2) != 2) {
        fprintf(stderr,"write error\n");
    }

    if (read(fd,buf,1) != 1) {
        fprintf(stderr,"read error\n");
    }
}