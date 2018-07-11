#ifndef BMCE_CORE_LOG_CONSOLELOGGER_H
#define BMCE_CORE_LOG_CONSOLELOGGER_H


#include <cstring>
#include <iostream>
#include <mutex>
#include <thread>

#include "core/log/logger.h"


namespace bmce
{

class ConsoleLogger: public Logger
{
private:
    std::mutex mutex_;

public:
    void log(
        Level level,
        const std::string& message,
        const std::string& function,
        const std::string& file,
        int line) override
    {
        std::lock_guard<std::mutex> lock(mutex_);

        auto pos = file.rfind('/');
        if (pos == file.npos)
        {
            pos = file.rfind('\\');
        }

        std::string file_base = pos == file.npos ? file : file.substr(pos + 1);

        std::cout
            << "THREAD(" << std::this_thread::get_id() << "):"
            << file_base << ":"
            << function << ":"
            << line << "  ";

        switch(level)
        {
            case Logger::Info:
                std::cout << "INFO: ";
                break;
            case Logger::Error:
                std::cout << "ERROR: ";
                break;
            case Logger::Warning:
                std::cout << "WARNING: ";
                break;
            case Logger::Debug:
                std::cout << "DEBUG: ";
                break;
            default:
                std::cout << "UNKNOWN: ";
                break;
        }

        std::cout << message << std::endl;
    }
};

} // namespace bmce


#endif
