#ifndef BMCE_CORE_LOG_LOG_H
#define BMCE_CORE_LOG_LOG_H


#include <sstream>

#include "core/log/logger.h"


#define BMCE_LOG(level, message)                         \
    {                                                    \
        std::ostringstream stream(std::ios_base::out);   \
        stream << message;                               \
        stream.flush();                                  \
                                                         \
        bmce::Log::log(                                  \
            level,                                       \
            stream.str(),                                \
            (const char*)(__func__),                     \
            __FILE__,                                    \
            __LINE__);                                   \
    }

#define BMCE_INFO(message) \
    BMCE_LOG(bmce::Logger::Info, message)

#define BMCE_ERROR(message) \
    BMCE_LOG(bmce::Logger::Error, message)

#define BMCE_WARNING(message) \
    BMCE_LOG(bmce::Logger::Warning, message)

#define BMCE_DEBUG(message) \
    BMCE_LOG(bmce::Logger::Debug, message)


namespace bmce
{

class Log
{
private:
    static Logger* logger_;

public:
    Log() = default;
    virtual ~Log() = default;

    Log(Log&& o) = default;
    Log& operator=(Log&& rhs) = default;

    Log(const Log& o) = default;
    Log& operator=(const Log& rhs) = default;

    static Logger* logger()
    {
        return logger_;
    }

    static void setLogger(Logger* logger)
    {
        logger_ = logger;
    }

    static void log(
        Logger::Level level,
        const std::string& message,
        const std::string& function,
        const std::string& file,
        int line)
    {
        if (logger_ != nullptr)
        {
            logger_->log(level, message, function, file, line);
        }
    }
};

} // namespace bmce


#endif
