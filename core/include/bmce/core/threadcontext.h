#ifndef BMCE_CORE_THREADCONTEXT_H
#define BMCE_CORE_THREADCONTEXT_H


#include <functional>
#include <iostream>
#include <mutex>
#include <thread>


namespace bmce
{


class ThreadContext
{
private:
    std::thread::id main_thread_id_{std::this_thread::get_id()};
    std::thread thread_;
    std::mutex mutex_;

public:
    ThreadContext() = default;

    explicit ThreadContext(const std::thread::id& main_thread_id) :
        main_thread_id_(main_thread_id)
    {
    }

    virtual ~ThreadContext()
    {
        if (thread_.joinable())
        {
            thread_.join();
        }
    }

    std::thread::id threadId()
    {
        return thread_.joinable() ? thread_.get_id() : main_thread_id_;
    }

    bool isMain()
    {
        return !thread_.joinable();
    }

    bool isRunning()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return thread_.joinable();
    }

    void start()
    {
        if (!thread_.joinable())
        {
            thread_ = std::thread(&ThreadContext::loop, this);
        }
    }

    virtual void loop() = 0;
};


} // namespace bmce


#endif
