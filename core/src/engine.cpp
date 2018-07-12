#include "core/engine.h"

#include <SDL.h>

#include "core/log/log.h"


namespace
{


int SDLCALL watch(void* userdata, SDL_Event* event)
{
    auto engine = static_cast<bmce::Engine*>(userdata);
    if (engine == nullptr)
    {
        return 1;
    }

    if (event->type == SDL_MOUSEMOTION)
    {
        engine->cursor_moved.emit(event->motion.x, event->motion.y);
    }
    else if (event->type == SDL_KEYDOWN)
    {
        engine->key_down.emit(event->key.keysym.sym);
    }
    else if (event->type == SDL_KEYUP)
    {
        engine->key_up.emit(event->key.keysym.sym);
    }
    else if (
        event->type == SDL_WINDOWEVENT_SIZE_CHANGED ||
        event->type == SDL_WINDOWEVENT_RESIZED)
    {
        int width = event->window.data1;
        int height = event->window.data2;
        engine->window_resized.emit(width, height);
    }
    else if(event->type == SDL_QUIT)
    {
        engine->stop();
    }

    return 1;
}


} // namespace


namespace bmce
{


Engine::Engine()
{
    slot(started.connect([](){BMCE_INFO("Engine started")}));
    slot(stopped.connect([](){BMCE_INFO("Engine stopped")}));
    slot(key_down.connect([](unsigned int key){
        BMCE_INFO("Key down: " << key)}));
    slot(key_up.connect([](unsigned int key){
        BMCE_INFO("Key up: " << key)}));
    slot(cursor_moved.connect([](int x, int y){
        BMCE_INFO("Cursor moved: x=" << x << ", y=" << y)}));
    slot(cursor_moved.connect([](int x, int y){
        BMCE_INFO("Cursor moved: x=" << x << ", y=" << y)}));
}

void Engine::run()
{
    started.emit();

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS) != 0)
    {
        BMCE_ERROR("Failed to initialize SDL: " << SDL_GetError())
        return;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Engine",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        SDL_WINDOW_OPENGL);

    SDL_AddEventWatch(watch, this);

    loop();

    stopped.emit();
}

void Engine::stop()
{
    stopped_ = true;
}

void Engine::loop()
{
    stopped_ = false;

    while (!stopped_)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event) != 0) {}
    }
}


} // namespace bmce
