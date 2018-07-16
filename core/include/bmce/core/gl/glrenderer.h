#ifndef BMCE_CORE_GL_GLRENDERER_H
#define BMCE_CORE_GL_GLRENDERER_H


#include <string>

#include "core/renderer.h"


namespace bmce
{


namespace detail
{
struct GLRendererImpl;
} // namespace detail


class Test
{
private:
    std::string str_;
public:
    explicit Test(std::string str);
};




class GLRenderer : public Renderer
{
private:
    std::unique_ptr<detail::GLRendererImpl> impl_;

    std::string title_;
    int width_{640};
    int height_{480};

public:
    explicit GLRenderer(std::string title);
    GLRenderer(std::string title, int width, int height);

    GLRenderer(const GLRenderer& copy) = delete;
    GLRenderer(GLRenderer&& from) noexcept;

    ~GLRenderer() override;

    GLRenderer& operator=(const GLRenderer& copy) = delete;
    GLRenderer& operator=(GLRenderer&& from) noexcept;

    void resize(int width, int height) override;
    void render(const Scene& scene) override;

private:
    void init(int width, int height);
    void destroy();
    void setup();

};


}  // namespace bmce


#endif
