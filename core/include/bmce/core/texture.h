#ifndef BMCE_CORE_TEXTURE_H
#define BMCE_CORE_TEXTURE_H


#include <vector>

#include "core/colortypes.h"
#include "core/mathlib.h"
#include "core/rect.h"


namespace bmce
{

class Texture
{
public:
    using Data = std::vector<RGBA8>;

private:
    int width_;
    int height_;
    Data data_;

public:
    Texture();
    Texture(int width, int height);

    int width() const;
    int height() const;

    Data& data();
    const Data& data() const;

    void resize(int width, int height);
    void fill(const RGBA8& color);
    void fill(const RGBA8& color, const Rect<int>& rect);
    RGBA8& pixel(int x, int y);

    void sub(const Texture& texture, int x, int y);

    bool operator==(const Texture& r);
    bool operator!=(const Texture& r);
};

} // namespace bmce


#endif
