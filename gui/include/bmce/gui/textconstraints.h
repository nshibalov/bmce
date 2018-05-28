#ifndef BMCE_GUI_TEXTCONSTRAINTS_H
#define BMCE_GUI_TEXTCONSTRAINTS_H


#include "core/colortypes.h"
#include "gui/ustring.h"


namespace bmce
{

class TextConstraints
{
private:
    int width_;

public:
    TextConstraints();
    explicit TextConstraints(int width);

    int width() const;
    void setWidth(int width);

    bool isNewLine(UChar c);
};

} // namespace bmce


#endif
