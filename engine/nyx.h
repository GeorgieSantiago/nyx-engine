#pragma once

#include "common/module.h"
#include "common/logger.h"
#include "common/input.h"

class Nyx
{
private:
    int should_stop;
public:
    MLogger* logger;
    MInput* input;
    int startup();
    int shutdown();
    int is_running();
    void run();
    void trigger_stop();
};