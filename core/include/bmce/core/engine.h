#ifndef BMCE_CORE_ENGINE_H
#define BMCE_CORE_ENGINE_H


#include <chrono>

#include "core/log/log.h"
#include "threadcontext.h"


namespace bmce
{


class Engine : public ThreadContext
{
public:
    Engine() = default;
    ~Engine() override = default;

    Engine(Engine&& from) = delete;
    Engine& operator=(Engine&& rhs) = delete;

    Engine(const Engine& from) = delete;
    Engine& operator=(const Engine& rhs) = delete;

    void run() override
    {
        BMCE_INFO("Engine started")

        loop();

        BMCE_INFO("Engine stopped")
    }

private:

    template<typename T>
    static void testf(T interval)
    {
        for(int i = 0; i < 10; ++i)
        {
            BMCE_INFO("Thick: " << i)
            std::this_thread::sleep_for(interval);
        }
    }

    void loop()
    {
        using std::chrono_literals::operator""s;

        std::thread t1([]() { testf(0.1s); });
        std::thread t2([]() { testf(0.1s); });

        testf(0.2s);

        t1.join();
        t2.join();
    }

};


} // namespace bmce


#endif
