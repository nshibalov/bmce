#ifndef BMCE_CORE_LOG_LOGGER_H
#define BMCE_CORE_LOG_LOGGER_H


#include <string>


namespace bmce
{

class Logger
{
public:
    enum Level
    {
        Info,
        Error,
        Warning,
        Debug
    };

public:
    virtual void log(
        Level level,
        const std::string& msg,
        const std::string& function,
        const std::string& file,
        int line) = 0;
};

} // namespace bmce


#endif
