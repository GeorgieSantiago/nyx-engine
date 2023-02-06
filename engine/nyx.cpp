#include "nyx.h"

int Nyx::startup()
{
    should_stop = 0;
    logger = &MLogger();
    logger->startup();
    logger->log_message("Logger online");
    input = &MInput();
    input->startup();
    logger->log_message("Listening to input");
    return 1;
}

int Nyx::shutdown()
{
    logger->shutdown();
    logger = nullptr;

    input->shutdown();
    input = nullptr;
    
    return 1;
}

void Nyx::run()
{
    logger->log_message("Running Nyx Engine");
    while(is_running() == 1)
    {

    }
}

int Nyx::is_running()
{
    if (should_stop == 1) return 0;
    return 1;
}

void Nyx::trigger_stop()
{
    logger->log_message("Stopping Engine");
    should_stop = 0;
}