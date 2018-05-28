#ifndef BMCE_CORE_LOG_CONSOLELOGGER_H
#define BMCE_CORE_LOG_CONSOLELOGGER_H


#include <cstring>
#include <iostream>

#include "core/log/logger.h"


namespace bmce
{

class ConsoleLogger: public Logger
{
public:
    void log(
        Level level,
        const std::string& message,
        const std::string& function,
        const std::string& file,
        int line) override
    {
        auto pos = file.rfind('/');
        if (pos == file.npos)
        {
            pos = file.rfind('\\');
        }

        std::string file_base = pos == file.npos ? file : file.substr(pos + 1);

        std::cout
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
