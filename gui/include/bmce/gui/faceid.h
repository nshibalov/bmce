#ifndef BMCE_GUI_FACEID_H
#define BMCE_GUI_FACEID_H


#include <string>


namespace bmce
{

class FaceId
{
public:
    using Byte = unsigned char;
    using Size = signed long;

private:
    std::string file_name_;
    const Byte* data_;
    Size data_size_;
    int index_;

public:
    FaceId();
    FaceId(const std::string& file_name);
    FaceId(const Byte* data, Size data_size);

    const std::string& fileName() const;
    const Byte* data() const;
    Size dataSize() const;
    int index() const;
};

} // namespace bmce


#endif
