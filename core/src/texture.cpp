#include "core/texture.h"


#include <algorithm>
#include <cstring>
#include <iostream>

#include "core/utils.h"


namespace bmce
{

Texture::Texture() :
    width_(0),
    height_(0)
{
}

Texture::Texture(int width, int height) :
    width_(0),
    height_(0)
{
    resize(width, height);
}

int Texture::width() const
{
    return width_;
}

int Texture::height() const
{
    return height_;
}

Texture::Data& Texture::data()
{
    return data_;
}

const Texture::Data& Texture::data() const
{
    return data_;
}

void Texture::resize(int width, int height)
{
    width_ = width;
    height_ = height;
    data_.resize(width_ * height_);
}

void Texture::fill(const RGBA8& color)
{
    std::fill(data_.begin(), data_.end(), color);
}

void Texture::fill(const RGBA8& color, const Rect<int>& rect)
{
    int x = std::max(0, rect.x0);
    int y = std::max(0, rect.y0);
    int xm = std::min(width_, rect.x1 + 1);
    int ym = std::min(height_, rect.y1 + 1);
    for (; y < ym; ++y)
    {
        std::fill(
            data_.begin() + y * width_ + x,
            data_.begin() + y * width_ + xm,
            color);
    }
}

RGBA8& Texture::pixel(int x, int y)
{
    return data_[y * width() + x];
}

void Texture::sub(const Texture& texture, int x, int y)
{
    for (int i = y, p = 0; i < texture.height() + y; ++i, ++p)
    {
        for (int j = x, q = 0; j < texture.width() + x; ++j, ++q)
        {
            if (i < 0 || j < 0 || i >= height() || j >= width())
            {
                continue;
            }

            RGBA8& bg = data()[i * width() + j];
            const RGBA8& fg = texture.data()[p * texture.width() + q];

            bg.blend(fg);
        }
    }
}


bool Texture::operator==(const Texture& r)
{
    return data_ == r.data_;
}

bool Texture::operator!=(const Texture& r)
{
    return data_ != r.data_;
}

} // namespace bmce
