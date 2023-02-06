#pragma once

#include "module.h"
#include "glog/logging.h"
#include <iostream>

class MLogger : public Module
{
public:
    int startup() override;
    int shutdown() override;
    void log_message(char* message);
    void log_error(char* message);
};