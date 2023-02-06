#include "logger.h"

int MLogger::startup()
{
    google::InitGoogleLogging("C");
    return 1;
}

int MLogger::shutdown()
{
    google::ShutdownGoogleLogging();
    return 1;
}

void MLogger::log_message(char* message)
{
    LOG(INFO) << message;
    std::cout << "[ENGINE]: " << message << std::endl;

}

void MLogger::log_error(char* message)
{
    LOG(ERROR) << message;
    std::cout << message << std::endl;
}