#ifndef BMCE_CORE_MOUSE_H
#define BMCE_CORE_MOUSE_H


#include "core/signal.h"
#include "object.h"


namespace bmce
{


struct Mouse : public Object
{
    using CursorMovedSignal = Signal<int, int>;

    CursorMovedSignal cursor_moved;
};


} // namespace bmce


#endif
