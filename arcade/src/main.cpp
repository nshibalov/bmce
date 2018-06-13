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

#include <GLFW/glfw3.h>


class GuiGl : public bmce::Gui
{
private:
    bmce::GLTexture gl_texture_;

    bmce::Mesh mesh_;
    bmce::GLMesh glMesh_;

public:
    GuiGl() :
        mesh_(bmce::Mesh::FromRect(bmce::Rect<bmce::FPType>(-1, -1, 1, 1), -1)),
        glMesh_(mesh_)
    {
    }

    void resize(int width, int height)
    {
        bmce::Gui::resize(width, height);
        gl_texture_.init(texture());
    }

    void draw(const bmce::GLShader& shader)
    {
        update();

        int texture_unit = 2;
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
    int width_;
    int height_;

    GuiGl gui_gl_;

    bmce::Texture texture_;
    bmce::GLTexture gl_texture_;
    bmce::Camera camera_;
    bmce::GLShader shader_;

    std::vector<bmce::Mesh> meshes_;
    std::vector<bmce::GLMesh> glMeshes_;

public:
    Program(int width, int height) :
        width_(width),
        height_(height),
        texture_(1, 1)
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

    void update(double dt, bool l, bool r, bool f, bool b)
    {
        float step = 10.0f * static_cast<float>(dt);
        if (l) { camera_.right(-step); }
        if (r) { camera_.right( step); }
        if (f) { camera_.forward( step); }
        if (b) { camera_.forward(-step); }
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

void ResizeCallback(GLFWwindow* window, int width, int height)
{
    auto program = static_cast<Program*>(glfwGetWindowUserPointer(window));
    program->resize(width, height);
}

void SetCursorPosCallback(GLFWwindow* window, double x, double y)
{
    auto program = static_cast<Program*>(glfwGetWindowUserPointer(window));
    program->cursorMoved(&x, &y);
    glfwSetCursorPos(window, x, y);
}

int main(int /*argc*/, char** /*argv*/)
{
    bmce::ConsoleLogger logger;
    bmce::Loggable::setLogger(&logger);

    int width = 640;
    int height = 480;

    glfwInit();
    GLFWwindow* pWindow = glfwCreateWindow(
        width, height, "Arcade", nullptr, nullptr);
    glfwMakeContextCurrent(pWindow);
    glewInit();

    Program program(width, height);

    glfwSetWindowUserPointer(pWindow, &program);
    glfwSetWindowSizeCallback(pWindow, ResizeCallback);
    glfwSetCursorPosCallback(pWindow, SetCursorPosCallback);

    double dt = 0.01;
    double accumulator = 0.0;
    double current_time = glfwGetTime();
    while (glfwWindowShouldClose(pWindow) == 0)
    {
        glfwPollEvents();

        double new_time = glfwGetTime();
        accumulator += new_time - current_time;
        current_time = new_time;

        while (accumulator >= dt)
        {
            program.update(
                dt,
                glfwGetKey(pWindow, GLFW_KEY_LEFT) == GLFW_PRESS,
                glfwGetKey(pWindow, GLFW_KEY_RIGHT) == GLFW_PRESS,
                glfwGetKey(pWindow, GLFW_KEY_UP) == GLFW_PRESS,
                glfwGetKey(pWindow, GLFW_KEY_DOWN) == GLFW_PRESS);
            accumulator -= dt;
        }

        program.draw();
        glfwSwapBuffers(pWindow);
    }

    glfwTerminate();
}
