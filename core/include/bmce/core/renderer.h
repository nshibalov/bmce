#ifndef BMCE_CORE_RENDERER_H
#define BMCE_CORE_RENDERER_H


#include "core/scene.h"


namespace bmce
{


class Renderer
{
public:
    Renderer() = default;
    Renderer(Renderer&& o) = default;
    Renderer(const Renderer& o) = default;
    virtual ~Renderer() = default;

    Renderer& operator=(Renderer&& o) = default;
    Renderer& operator=(const Renderer& o) = default;

    virtual void resize(int width, int height)
    {
    }

    virtual void render(const Scene& scene)
    {
    }
};

}  // namespace bmce


#endif
