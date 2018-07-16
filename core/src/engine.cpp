#include "core/engine.h"


#include <SDL.h>

#include "core/errors/commonerror.h"
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
    started.connect([]() { BMCE_INFO("Engine started") });
    stopped.connect([]() { BMCE_INFO("Engine stopped") });
    key_down.connect(
        [](unsigned int key)
        { BMCE_INFO("Key down: " << key) });
    key_up.connect(
        [](unsigned int key)
        { BMCE_INFO("Key up: " << key)});
    cursor_moved.connect(
        [](int x, int y)
        { BMCE_INFO("Cursor moved: x=" << x << ", y=" << y)});

    init();
}


Renderer* Engine::renderer()
{
    return renderer_.get();
}


void Engine::setRenderer(std::unique_ptr<Renderer> renderer)
{
    renderer_ = std::move(renderer);
}


void Engine::run()
{
    started.emit();

    loop();
    destroy();

    stopped.emit();
}


void Engine::stop()
{
    stopped_ = true;
}


void Engine::init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
    {
        throw CommonError(
            "Failed to initialize SDL: " + std::string(SDL_GetError()));
    }

    SDL_AddEventWatch(watch, this);
}


void Engine::destroy()
{
    renderer_.reset();

    BMCE_INFO("Engine::destroy()")

    SDL_DelEventWatch(watch, nullptr);
    SDL_Quit();
}


void Engine::loop()
{
    stopped_ = false;

    int accumulator = 0;
    int current_time = SDL_GetTicks();

    while (!stopped_)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event) != 0) {}

        int new_time = SDL_GetTicks();
        accumulator += new_time - current_time;
        current_time = new_time;

        while (accumulator >= Engine::UPDATE_INTERVAL_MS)
        {
            update(Engine::UPDATE_INTERVAL_MS);
            accumulator -= Engine::UPDATE_INTERVAL_MS;

            if (accumulator < Engine::UPDATE_INTERVAL_MS && accumulator != 0)
            {
                if (update(accumulator))
                {
                    accumulator = 0;
                }
            }
        }

        if (renderer_)
        {
            Scene scene;
            renderer_->render(scene);
        }
    }
}


bool Engine::update(int ms)
{
    if (ms == Engine::UPDATE_INTERVAL_MS)
    {
        BMCE_INFO("update (" << ms << "ms)")
        return true;
    }

    BMCE_INFO("update leftover: " << ms << "ms")
    return false;
}




} // namespace bmce
