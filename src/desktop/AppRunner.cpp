//
// Created by kivi on 23.05.17.
//

#include <unistd.h>

#include "AppRunner.h"
#include "Config.h"

void AppRunner::execute() {
    printf("executing %s\n", app_.executable.c_str());
    pid_t pid = fork();
    if (pid == 0) {
        execv(app_.executable.c_str(), (char *const[]) {"phone", NULL});
    }
}