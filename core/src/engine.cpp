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
        engine->mouse().cursor_moved.emit(event->motion.x, event->motion.y);
    }
    else if (event->type == SDL_KEYDOWN && event->key.repeat == 0)
    {
        engine->keyboard().key_down.emit(
            bmce::sdl_keycode_to_vk(event->key.keysym.sym));
    }
    else if (event->type == SDL_KEYUP)
    {
        engine->keyboard().key_up.emit(
            bmce::sdl_keycode_to_vk(event->key.keysym.sym));
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
    keyboard().key_down.connect(
        [](unsigned int key)
        { BMCE_INFO("Key down: " << key) });
    keyboard().key_up.connect(
        [](unsigned int key)
        { BMCE_INFO("Key up: " << key)});
    mouse().cursor_moved.connect(
        [](int x, int y)
        { BMCE_INFO("Cursor moved: x=" << x << ", y=" << y)});

    init();
}


Keyboard& Engine::keyboard()
{
    return keyboard_;
}


const Keyboard& Engine::keyboard() const
{
    return keyboard_;
}


Mouse& Engine::mouse()
{
    return mouse_;
}


const Mouse& Engine::mouse() const
{
    return mouse_;
}


Renderer* Engine::renderer()
{
    return renderer_;
}


void Engine::setRenderer(Renderer* renderer)
{
    renderer_ = renderer;
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


void Engine::addScene(Scene* scene)
{
    addScene(scene, 0);
}


void Engine::addScene(Scene* scene, int priority)
{
    scenes_.insert(std::make_pair(scene, priority));
    updateSortedScenes();
}

void Engine::removeScene(Scene* scene)
{
    scenes_.erase(scene);
    updateSortedScenes();
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
            update();

            accumulator -= Engine::UPDATE_INTERVAL_MS;
        }

        partialUpdate(accumulator);
        render();
    }
}


void Engine::updateSortedScenes()
{
    sorted_scenes_.clear();
    sorted_scenes_.reserve(scenes_.size());

    for (auto& pair : scenes_)
    {
        sorted_scenes_.push_back(pair.first);
    }

    std::sort(sorted_scenes_.begin(), sorted_scenes_.end(),
        [this](const auto lhs, const auto rhs)
        {
            return scenes_[lhs] < scenes_[rhs];
        });
}


void Engine::update()
{
    for (auto scene : sorted_scenes_)
    {
        if (!scene->isActive())
        {
            continue;
        }

        scene->update(Engine::UPDATE_INTERVAL_MS);
    }
}


void Engine::partialUpdate(int ms)
{
    if (ms <= 0)
    {
        return;
    }

    for (auto scene : sorted_scenes_)
    {
        if (!scene->isActive())
        {
            continue;
        }

        scene->partialUpdate(Engine::UPDATE_INTERVAL_MS, ms);
    }
}


void Engine::render()
{
    if (renderer_ == nullptr)
    {
        return;
    }

    for (auto scene : sorted_scenes_)
    {
        if (!scene->isActive())
        {
            continue;
        }

        renderer_->render(*scene);
    }
}


} // namespace bmce
