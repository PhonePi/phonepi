//
// Created by kivi on 23.05.17.
//

#include <unistd.h>
#include <sstream>
#include <iostream>

#include "AppRunner.h"
#include "Config.h"

int makeargs(const char *args, int *argc, char ***aa) {
    char *buf = strdup(args);
    int c = 1;
    char *delim;
    char **argv = (char **) calloc(c, sizeof (char *));

    argv[0] = buf;

    while (delim = strchr(argv[c - 1], ' ')) {
        argv = (char **) realloc(argv, (c + 1) * sizeof (char *));
        argv[c] = delim + 1;
        *delim = 0x00;
        c++;
    }

    *argc = c;
    *aa = argv;

    return c;
}


void AppRunner::execute() {
    pid_t pid = fork();
    if (pid == 0) {
        if (not app_.path.empty()) chdir(app_.path.c_str());

        int argc;
        char** argv;
        makeargs(app_.executable.c_str(), &argc, &argv);

        execv(argv[0], argv);
    }
}

