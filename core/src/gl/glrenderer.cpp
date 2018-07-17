#include "core/gl/glrenderer.h"


#include <SDL.h>

#include "core/gl/gl.h"
#include "core/log/log.h"


namespace bmce
{


namespace detail
{

struct GLRendererImpl
{
    SDL_Window* window{nullptr};
    SDL_GLContext context{nullptr};
};

} // namespace detail


GLRenderer::GLRenderer(std::string title) :
    impl_(std::make_unique<detail::GLRendererImpl>()),
    title_(std::move(title))
{
    init(width_, height_);
}


GLRenderer::GLRenderer(std::string title, int width, int height) :
    impl_(std::make_unique<detail::GLRendererImpl>()),
    title_(std::move(title)),
    width_(width),
    height_(height)
{
    init(width_, height_);
}


GLRenderer::GLRenderer(GLRenderer&& o) noexcept :
    impl_(std::make_unique<detail::GLRendererImpl>(*o.impl_)),
    title_(std::move(o.title_)),
    width_(o.width_),
    height_(o.height_)
{
}


GLRenderer::~GLRenderer()
{
    BMCE_INFO("~GLRenderer")
    destroy();
}


GLRenderer& GLRenderer::operator=(GLRenderer&& o) noexcept
{
    impl_ = std::make_unique<detail::GLRendererImpl>(*o.impl_),
    title_ = std::move(o.title_);
    width_ = o.width_;
    height_ = o.height_;

    return *this;
}


void GLRenderer::resize(int width, int height)
{
    width_ = width;
    height_ = height;
    glViewport(0, 0, width_, height_);
}


void GLRenderer::render(const Scene& scene)
{
    SDL_GL_MakeCurrent(impl_->window, impl_->context);
    SDL_GL_SwapWindow(impl_->window);
}


void GLRenderer::init(int width, int height)
{
    impl_->window = SDL_CreateWindow(
        "Arcade",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_OPENGL);

    impl_->context = SDL_GL_CreateContext(impl_->window);

    glewInit();

    setup();
}


void GLRenderer::destroy()
{
    SDL_GL_DeleteContext(impl_->context);
    SDL_DestroyWindow(impl_->window);
}


void GLRenderer::setup()
{
    resize(width_, height_);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);

    SDL_GL_MakeCurrent(impl_->window, impl_->context);
    SDL_GL_SwapWindow(impl_->window);
}


}  // namespace bmce
