#ifndef BMCE_GUI_FONT_H
#define BMCE_GUI_FONT_H


#include <string>

#include "core/colortypes.h"


namespace bmce
{

class Font
{
private:
    std::string name_;

    size_t size_ = 12;
    FPType rotation_ = 0.0;

    RGBA8 color_;

    RGBA8 outline_color_;
    int outline_size_ = 0;

    RGBA8 background_color_;
    bool use_background_color_ = false;


public:
    Font() :
        name_("")
    {
    }

    Font(const std::string& name, size_t size) :
        name_(name),
        size_(size)
    {
    }

    const std::string name() const
    {
        return name_;
    }

    void setName(const std::string& name)
    {
        name_ = name;
    }

    size_t size() const
    {
        return size_;
    }

    void setSize(size_t size)
    {
        size_ = size;
    }

    FPType rotation()
    {
        return rotation_;
    }

    void setRotation(FPType rotation)
    {
        rotation_ = rotation;
    }

    const RGBA8& color() const
    {
        return color_;
    }

    void setColor(const RGBA8& color)
    {
        color_ = color;
    }

    const RGBA8& outlineColor() const
    {
        return outline_color_;
    }

    void setOutlineColor(const RGBA8& outline_color)
    {
        outline_color_ = outline_color;
    }

    int outlineSize()
    {
        return outline_size_;
    }

    void setOutlineSize(int outlineSize)
    {
        outline_size_ = outlineSize;
    }

    const RGBA8& backgroundColor() const
    {
        return background_color_;
    }

    void setBackgroundColor(const RGBA8& background_color)
    {
        background_color_ = background_color;
    }

    bool useBackgroundColor()
    {
        return use_background_color_;
    }

    void setUseBackgroundColor(bool use_background_color)
    {
        use_background_color_ = use_background_color;
    }
};

}  // namespace bmce


#endif
