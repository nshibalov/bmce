#ifndef BMCE_CORE_RENDERER_H
#define BMCE_CORE_RENDERER_H


#include "core/scene.h"


namespace bmce
{


class Renderer
{
public:
    Renderer() = default;
    Renderer(Renderer&& from) = default;
    Renderer(const Renderer& copy) = default;
    virtual ~Renderer() = default;

    Renderer& operator=(Renderer&& from) = default;
    Renderer& operator=(const Renderer& copy) = default;

    virtual void resize(int width, int height)
    {
    }

    virtual void render(const Scene& scene)
    {
    }
};

}  // namespace bmce


#endif
