#ifndef BMCE_CORE_MAINLOOP_H
#define BMCE_CORE_MAINLOOP_H


#include <functional>
#include <mutex>
#include <queue>


namespace bmce
{


class MainLoop
{
private:
    std::queue<std::function<void()>> deferred_calls_;
    std::mutex mutex_;

public:
    template<typename ...ARGS>
    void addDeferredCall(void(*func)(ARGS...), ARGS&&... args)
    {
        std::lock_guard<std::mutex> lock(mutex_);

        deferred_calls_.push([func, &args...] {
            func(std::forward<ARGS>(args)...);
        });
    }

    template<typename T, typename ...ARGS>
    void addDeferredCall(void(T::*func)(ARGS...), T* obj, ARGS&&... args)
    {
        std::lock_guard<std::mutex> lock(mutex_);

        deferred_calls_.push([func, obj, &args...] {
            (obj->*func)(std::forward<ARGS>(args)...);
        });
    }

    void triggerPendingDeferredCall()
    {
        std::lock_guard<std::mutex> lock(mutex_);

        if (!deferred_calls_.empty())
        {
            deferred_calls_.front()();
            deferred_calls_.pop();
        }
    }

    void triggerPendingDeferredCalls()
    {
        std::lock_guard<std::mutex> lock(mutex_);

        while (!deferred_calls_.empty())
        {
            deferred_calls_.front()();
            deferred_calls_.pop();
        }
    }

    virtual void loop() = 0;
};


} // namespace bmce


#endif
