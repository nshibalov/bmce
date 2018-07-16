#ifndef BMCE_CORE_ERROR_COMMONERROR_H
#define BMCE_CORE_ERROR_COMMONERROR_H


#include <exception>
#include <string>


namespace bmce
{


class CommonError : public std::exception
{
private:
    std::string message_;

public:
    CommonError() = default;
    explicit CommonError(std::string message) :
        message_(std::move(message))
    {
    }

    const std::string& message() const
    {
        return message_;
    }
};


} // namespace bmce


#endif
