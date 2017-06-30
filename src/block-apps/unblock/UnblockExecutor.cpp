//
// Created by kivi on 30.06.17.
//

#include "UnblockExecutor.h"

void UnblockExecutor::execute() {
    std::string kill = "pkill " + config_->getBlockProcess();
    system(kill.c_str());
    exit(0);
};