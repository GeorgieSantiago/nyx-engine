#pragma once

#include "module.h"
#include "logger.h"

class MInput : public Module
{
public:
    int startup() override;
    int shutdown() override;
};