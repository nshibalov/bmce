#ifndef BMCE_CORE_UTILS_H
#define BMCE_CORE_UTILS_H


#include <string>


namespace bmce
{

std::string ReadFileToString(const std::string& fname);

std::string& Replace(
        std::string& where, const std::string& what, const std::string& to);

std::string& LTrim(std::string& str, const std::string& what);

std::string& RTrim(std::string& str, const std::string& what);

std::string& Trim(std::string& str, const std::string& what);
} // namespace bmce


#endif
