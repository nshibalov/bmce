#include "gui/textconstraints.h"


namespace bmce
{

TextConstraints::TextConstraints() :
    width_(0)
{
}

TextConstraints::TextConstraints(int width) :
    width_(width)
{
}

int TextConstraints::width() const
{
    return width_;
}

void TextConstraints::setWidth(int width)
{
    width_ = width;
}

bool TextConstraints::isNewLine(UChar c)
{
    return '\n' == c;
}

} // namespace bmce
