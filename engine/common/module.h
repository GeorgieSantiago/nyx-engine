#pragma once

class Module
{
public:
    virtual int startup() {return 0;};
    virtual int shutdown() {return 0;};
};