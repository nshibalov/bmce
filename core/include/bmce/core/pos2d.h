#ifndef BMCE_CORE_POS2D_H
#define BMCE_CORE_POS2D_H


namespace bmce
{

template<typename T>
struct Pos2d
{
    T x, y;

    Pos2d() :
        x(0), y(0)
    {}

    Pos2d(T xx, T yy) :
        x(xx), y(yy)
    {}

    void set(T xx=0, T yy=0)
    {
        x = xx;
        y = yy;
    }

    void add(T xx, T yy)
    {
        x += xx;
        y += yy;
    }
};

} // namespace bmce


#endif
