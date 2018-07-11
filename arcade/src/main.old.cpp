#include "core/gl/glmesh.h"
#include "core/gl/glshader.h"
#include "core/gl/gltexture.h"
#include "core/log/consolelogger.h"

#include "core/camera.h"
#include "core/fileimport.h"
#include "core/mathlib.h"
#include "core/mesh.h"

#include "gui/gui.h"

#include <iostream>

#include <SDL.h>
#include <SDL_opengl.h>


class GuiGl : public bmce::Gui
{
private:
    bmce::Mesh mesh_;
    bmce::GLMesh glMesh_;
    bmce::GLTexture gl_texture_;

public:
    GuiGl() :
        bmce::Gui(),
        mesh_(
            bmce::Mesh::FromRect(
                bmce::Rect<bmce::FPType>(-1, -1, 1, 1),
                -1)),
        glMesh_(mesh_)
    {
        glMesh_;
    }

    void resize(int width, int height)
    {
        bmce::Gui::resize(width, height);
        gl_texture_.init(texture());
    }

    void draw(const bmce::GLShader& shader)
    {
        update();

        int texture_unit = 1;
        gl_texture_.sub(texture(), 0, 0);
        gl_texture_.bind(texture_unit);

        shader.setUniform(shader.getUniformId("texture0"), texture_unit);
        shader.setProjectionMatrix(camera().projectionMatrix());
        shader.setModelViewMatrix(camera().modelViewMatrix());

        glMesh_.draw();
    }
};

class Program
{
private:
    SDL_Window *window_{nullptr};

    int width_{0};
    int height_{0};
    bool quiting_{false};

    float xvel_{0.0};
    float yvel_{0.0};

    GuiGl gui_gl_;

    bmce::Texture texture_{1, 1};
    bmce::GLTexture gl_texture_;
    bmce::Camera camera_;
    bmce::GLShader shader_;

    std::vector<bmce::Mesh> meshes_{};
    std::vector<bmce::GLMesh> glMeshes_{};

public:
    Program(SDL_Window *window, int width, int height) :
        window_(window),
        width_(width),
        height_(height)
    {
        resize(width, height);

        texture_.fill(bmce::RGBA8(36, 45, 47));
        gl_texture_.init(texture_);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClearDepth(1.0f);

        shader_.init("data/shaders/lesson.vs", "data/shaders/lesson.fs");

        meshes_ = bmce::ImportStaticMesh("data/models/jet.obj");
        glMeshes_.resize(meshes_.size());
        for (size_t i = 0; i < meshes_.size(); ++i)
        {
            glMeshes_[i].init(meshes_[i]);
        }
    }

    SDL_Window* window()
    {
        return window_;
    }

    bool quiting()
    {
        return quiting_;
    }

    float xvel() { return xvel_; }
    void setXVel(float velocity) { xvel_ = velocity; }

    float yvel() { return yvel_; }
    void setYVel(float velocity) { yvel_ = velocity; }

    void setQuiting(bool quiting)
    {
        quiting_ = quiting;
    }

    void resize(int width, int height)
    {
        width_ = width;
        height_ = height;
        glViewport(0, 0, width_, height_);
        camera_.setPerspective(width_, height_);
        gui_gl_.resize(width_, height_);
    }

    void cursorMoved(double* x, double* y)
    {
        int cx = width_ / 2;
        int cy = height_ / 2;
        camera_.yaw((cx - static_cast<float>(*x)) * 0.1f);
        camera_.pitch((cy - static_cast<float>(*y)) * 0.1f);
        *x = cx;
        *y = cy;
    }

    void update(double dt)
    {
        float step = 10.0f * static_cast<float>(dt);

        camera_.right(step * xvel_);
        camera_.forward(step * yvel_);
    }

    void draw()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        int texture_unit = 1;
        gl_texture_.bind(texture_unit);

        shader_.bind();
        shader_.setUniform(shader_.getUniformId("texture0"), texture_unit);
        shader_.setProjectionMatrix(camera_.projectionMatrix());
        shader_.setModelViewMatrix(camera_.modelViewMatrix());

        for (
            std::vector<bmce::GLMesh>::const_iterator it = glMeshes_.begin();
            it != glMeshes_.end();
            ++it)
        {
            it->draw();
        }

        gui_gl_.draw(shader_);
    }
};


int SDLCALL watch(void* userdata, SDL_Event* event)
{
    auto program = static_cast<Program*>(userdata);
    if (program == nullptr)
    {
        return 1;
    }

    if (event->type == SDL_MOUSEMOTION)
    {
        double x = event->motion.x;
        double y = event->motion.y;
        program->cursorMoved(&x, &y);
        SDL_WarpMouseInWindow(program->window(), x, y);
    }
    else if (event->type == SDL_KEYDOWN)
    {
        switch(event->key.keysym.sym)
        {
            case SDLK_LEFT:
                program->setXVel(-1);
                break;
            case SDLK_RIGHT:
                program->setXVel( 1);
                break;
            case SDLK_UP:
                program->setYVel( 1);
                break;
            case SDLK_DOWN:
                program->setYVel(-1);
                break;
            default:
                break;
        }
    }
    else if (event->type == SDL_KEYUP)
    {
        switch(event->key.keysym.sym)
        {
            case SDLK_LEFT:
                if (program->xvel() < 0) { program->setXVel(0); }
                break;
            case SDLK_RIGHT:
                if (program->xvel() > 0) { program->setXVel(0); }
                break;
            case SDLK_UP:
                if (program->yvel() > 0) { program->setYVel(0); }
                break;
            case SDLK_DOWN:
                if (program->yvel() < 0) { program->setYVel(0); }
                break;
            default:
                break;
        }
    }
    else if (
        event->type == SDL_WINDOWEVENT_SIZE_CHANGED ||
        event->type == SDL_WINDOWEVENT_RESIZED)
    {
        int width = event->window.data1;
        int height = event->window.data2;
        program->resize(width, height);
    }
    else if(event->type == SDL_QUIT)
    {
        program->setQuiting(true);
    }

    return 1;
}


int main(int /*argc*/, char** /*argv*/)
{
    int width = 640;
    int height = 480;

    // SDL

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS) != 0)
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Arcade",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_OPENGL);

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);

    SDL_AddEventWatch(watch, nullptr);

    glewInit();

    bmce::ConsoleLogger logger;
    bmce::Loggable::setLogger(&logger);

    Program program(window, width, height);

    SDL_AddEventWatch(watch, &program);

    int dt = 10; // ms
    int accumulator = 0;
    int current_time = SDL_GetTicks();

    while (!program.quiting())
    {
        SDL_Event event;
        while(SDL_PollEvent(&event) != 0) {}

        int new_time = SDL_GetTicks();
        accumulator += new_time - current_time;
        current_time = new_time;

        while (accumulator >= dt)
        {
            program.update(dt / 1000.0);
            accumulator -= dt;
        }

        SDL_GL_MakeCurrent(window, gl_context);
        program.draw();
        SDL_GL_SwapWindow(window);
    }

    bmce::Loggable::setLogger(nullptr);

    SDL_DelEventWatch(watch, nullptr);
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
