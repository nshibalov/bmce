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

    enum
    {
        UPDATE_INTERVAL_MS = 10
    };

private:
    bool stopped_{false};

public:
    Engine();

    Engine(Engine&& from) = delete;
    Engine& operator=(Engine&& rhs) = delete;

    Engine(const Engine& from) = delete;
    Engine& operator=(const Engine& rhs) = delete;

    ~Engine() override = default;

    void test();
    virtual bool update(int ms);

    void run() override;
    void stop();

private:
    void loop();

};


} // namespace bmce


#endif
