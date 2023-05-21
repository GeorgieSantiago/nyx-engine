#include "logger.h"

MLogger* MLogger::instance = nullptr;

int MLogger::startup()
{
    if (MLogger::instance == nullptr) {
        MLogger::instance = this;
    }
    google::InitGoogleLogging("C");
    return 1;
}

int MLogger::shutdown()
{
    MLogger::instance = nullptr;
    google::ShutdownGoogleLogging();
    return 1;
}

void MLogger::log_error(char* message)
{
    log_message(message, "[ERROR]");
}

void MLogger::log_error(std::runtime_error err)
{
    log_message(err.what(), "[ERROR]");
}

void MLogger::log_message(const char* message, char* prefix)
{
    LOG(INFO) << message;
    std::cout << prefix << " " << message << std::endl;
}

MLogger* MLogger::get()
{
    return MLogger::instance;
}

// void MLogger::log_message(Vec2 vector) 
// {
//     log_message((char*)vector.x + ',' + (char*)vector.y);
// }

// void MLogger::log_message(Vec3 vector) 
// {
//     log_message((char*)vector.x + ',' + (char*)vector.y + ',' + (char*)vector.z);
// }