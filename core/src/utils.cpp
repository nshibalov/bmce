#include "core/utils.h"

#include <fstream>
#include <iostream>


namespace bmce
{

std::string ReadFileToString(const std::string& fname)
{
    std::ifstream file(fname.c_str(), std::ios::in | std::ios::binary);
    if(file.fail())
    {
        return std::string();
    }

    file.seekg(0, std::ios::end);
    std::ifstream::pos_type new_size = file.tellg();

    std::string ret;
    ret.resize(static_cast<unsigned int>(new_size));

    file.seekg(0, std::ios::beg);
    file.read(&ret[0], new_size);
    file.close();

    return ret;
}

std::string& Replace(
    std::string& where, const std::string& what, const std::string& to)
{
    std::string::size_type currPos = 0;

    while((currPos = where.find(what, currPos)) != where.npos)
    {
        where.replace(currPos, what.size(), to);
        currPos += to.size();
    }

    return where;
}

std::string& LTrim(std::string& str, const std::string& what)
{
    str.erase(0, str.find_first_not_of(what));
    return str;
}

std::string& RTrim(std::string& str, const std::string& what)
{
    str.erase(str.find_last_not_of(what) + 1);
    return str;
}

std::string& Trim(std::string& str, const std::string& what)
{
    return LTrim(RTrim(str, what), what);
}

} // namespace bmce
