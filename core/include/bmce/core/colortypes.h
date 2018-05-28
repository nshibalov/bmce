#ifndef BMCE_CORE_COLORTYPES_H
#define BMCE_CORE_COLORTYPES_H


#include <cstdint>
#include <vector>

#include "core/mathlib.h"
#include "core/rect.h"
#include "core/types.h"


namespace bmce
{

struct RGB8
{
    UInt8 r = 0, g = 0, b = 0;

    RGB8() = default;

    RGB8(UInt8 rr, UInt8 gg, UInt8 bb) :
        r(rr), g(gg), b(bb) {}

    bool operator==(const RGB8& right) const
    {
        return r == right.r && g == right.g && b == right.b;
    }
};


struct RGBA8
{
    UInt8 r = 0, g = 0, b = 0, a = 255;

    RGBA8() = default;

    RGBA8(UInt8 rr, UInt8 gg, UInt8 bb) :
        r(rr), g(gg), b(bb) {}

    RGBA8(UInt8 rr, UInt8 gg, UInt8 bb, UInt8 aa) :
        r(rr), g(gg), b(bb), a(aa) {}

    bool operator==(const RGBA8& right) const
    {
        return r == right.r
            && g == right.g
            && b == right.b
            && a == right.a;
    }

    void blend(const RGBA8& right)
    {
        r = (r * (255 - right.a) + right.r * right.a) / 255;
        g = (g * (255 - right.a) + right.g * right.a) / 255;
        b = (b * (255 - right.a) + right.b * right.a) / 255;
        a = (a * (255 - right.a) + right.a * right.a) / 255;
    }
};

} // namespace bmce


#endif
