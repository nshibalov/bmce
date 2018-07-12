#ifndef BMCE_CORE_ENGINE_H
#define BMCE_CORE_ENGINE_H


#include "core/signal.h"
#include "object.h"
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

private:
    bool stopped_{false};

public:
    Engine();

    Engine(Engine&& from) = delete;
    Engine& operator=(Engine&& rhs) = delete;

    Engine(const Engine& from) = delete;
    Engine& operator=(const Engine& rhs) = delete;

    ~Engine() override = default;

    void run() override;
    void stop();

private:
    void loop();

};


} // namespace bmce


#endif
