#pragma once

#include "common/module.h"
#include "common/logger.h"
#include "common/input.h"
#include "renderer/renderer.h"
#include "math/vec3.h"
#include "string/nstring.h"

class Nyx
{
private:
    int should_stop;
public:
    MLogger* logger;
    MInput* input;
    Renderer* renderer;
    int startup();
    int shutdown();
    int is_running();
    void run();
    void trigger_stop();
};