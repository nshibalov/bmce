#include "gui/faceid.h"


namespace bmce
{
FaceId::FaceId() :
    data_(nullptr),
    data_size_(0),
    index_(0)
{
}

FaceId::FaceId(const std::string& file_name) :
    file_name_(file_name),
    data_(nullptr),
    data_size_(0),
    index_(0)
{
}

FaceId::FaceId(const Byte* data, Size data_size) :
    data_(data),
    data_size_(data_size),
    index_(0)
{
}

const std::string& FaceId::fileName() const
{
    return file_name_;
}

const FaceId::Byte* FaceId::data() const
{
    return data_;
}

FaceId::Size FaceId::dataSize() const
{
    return data_size_;
}

int FaceId::index() const
{
    return index_;
}

} // namespace bmce
