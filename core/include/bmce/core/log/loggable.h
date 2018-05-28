#ifndef BMCE_CORE_LOG_LOGGABLE_H
#define BMCE_CORE_LOG_LOGGABLE_H


#include <sstream>

#include "core/log/logger.h"


#define NW_LOG(level, message)                        \
    log(                                              \
        level,                                        \
        dynamic_cast<std::ostringstream&>(            \
            std::ostringstream().flush() << message   \
        ).str(),                                      \
        (const char*)(__func__),                      \
        __FILE__,                                     \
        __LINE__);                                    \

#define NW_INFO(message) \
    NW_LOG(bmce::Logger::Info, message)

#define NW_ERROR(message) \
    NW_LOG(bmce::Logger::Error, message)

#define NW_WARNING(message) \
    NW_LOG(bmce::Logger::Warning, message)

#define NW_DEBUG(message) \
    NW_LOG(bmce::Logger::Debug, message)


namespace bmce
{

class Loggable
{
private:
    static Logger* logger_;

public:
    Loggable() = default;
    virtual ~Loggable() = default;


    static Logger* logger()
    {
        return logger_;
    }

    static void setLogger(Logger* logger)
    {
        logger_ = logger;
    }

protected:
    void log(
        Logger::Level level,
        const std::string& message,
        const std::string& function,
        const std::string& file,
        int line) const
    {
        if (logger_ != nullptr)
        {
            logger_->log(level, message, function, file, line);
        }
    }
};

} // namespace bmce


#endif
