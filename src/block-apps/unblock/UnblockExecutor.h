//
// Created by kivi on 30.06.17.
//

#ifndef UNBLOCK_PI_UNBLOCKEXECUTOR_H
#define UNBLOCK_PI_UNBLOCKEXECUTOR_H

#include <QObject>

#include "Config.h"

class UnblockExecutor : public QObject {
    Q_OBJECT

public:

    UnblockExecutor(Config* config) : config_(config) {}

public slots:

    void execute();

private:

    Config* config_;

};

#endif //UNBLOCK_PI_UNBLOCKEXECUTOR_H
