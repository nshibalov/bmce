#ifndef BMCE_CORE_RECT_H
#define BMCE_CORE_RECT_H


namespace bmce
{

template<typename T>
struct Rect
{
    T x0, y0, x1, y1;

    Rect() :
        x0(0), y0(0), x1(0), y1(0)
    {}

    Rect(T x0, T y0, T x1, T y1) :
        x0(x0), y0(y0), x1(x1), y1(y1)
    {}

    bool zero() const
    {
        return x0 == 0
            && y0 == 0
            && x1 == 0
            && y1 == 0;
    }

    bool inside(T x, T y) const
    {
        return x >= x0 && x <= x1
            && y >= y0 && y <= y1;
    }

    T width() const
    {
        return x1 - x0;
    }

    T height() const
    {
        return y1 - y0;
    }

    void set(T nx0, T ny0, T nx1, T ny1)
    {
        x0 = nx0;
        y0 = ny0;
        x1 = nx1;
        y1 = ny1;
    }

    void reset()
    {
        x0 = 0;
        y0 = 0;
        x1 = 0;
        y1 = 0;
    }

    void add(T x, T y)
    {
        x0 += x;
        y0 += y;
        x1 += x;
        y1 += y;
    }

    void sub(T x, T y)
    {
        return add(-x, -y);
    }

    void include(T x, T y)
    {
        x0 = x0 < x ? x0 : x;
        y0 = y0 < y ? y0 : y;
        x1 = x1 > x ? x1 : x;
        y1 = y1 > y ? y1 : y;
    }

    void include(T nx0, T ny0, T nx1, T ny1)
    {
        x0 = x0 < nx0 ? x0 : nx0;
        y0 = y0 < ny0 ? y0 : ny0;
        x1 = x1 > nx1 ? x1 : nx1;
        y1 = y1 > ny1 ? y1 : ny1;
    }
};

} // namespace bmce


#endif
