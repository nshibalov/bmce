#ifndef BMCE_CORE_ENGINE_H
#define BMCE_CORE_ENGINE_H


#include <memory>

#include "core/signal.h"
#include "object.h"
#include "renderer.h"
#include "threadcontext.h"


namespace bmce
{


class Engine : public ThreadContext, public Object
{
public:
    Signal<> started;
    Signal<> stopped;

    Signal<unsigned int> key_down;
    Signal<unsigned int> key_up;
    Signal<int, int> cursor_moved;
    Signal<int, int> window_resized;

    enum
    {
        UPDATE_INTERVAL_MS = 10
    };

private:
    std::unique_ptr<Renderer> renderer_;
    bool stopped_{false};

public:
    Engine();

    Engine(Engine&& from) = delete;
    Engine& operator=(Engine&& rhs) = delete;

    Engine(const Engine& from) = delete;
    Engine& operator=(const Engine& rhs) = delete;

    ~Engine() override = default;

    Renderer* renderer();
    void setRenderer(std::unique_ptr<Renderer> renderer);

    void run() override;
    void stop();

private:
    void init();
    void destroy();

    void loop();
    virtual bool update(int ms);

};


} // namespace bmce


#endif
