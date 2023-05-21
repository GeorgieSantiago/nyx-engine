#pragma once

#include "module.h"
#include "glog/logging.h"
#include <iostream>
#include "../math/vec2.h"
#include "../math/vec3.h"

class MLogger : public Module
{
public:
    static MLogger* instance;
    int startup() override;
    int shutdown() override;
    void log_error(char* message);
    void log_error(std::runtime_error err);
    void log_message(const char* message, char* prefix = "[ENGINE]");
    static MLogger* get();
    // void log_message(Vec3* vector_3);
    // void log_message(Vec2*  vector2);
};