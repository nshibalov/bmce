#ifndef BMCE_CORE_THREADCONTEXT_H
#define BMCE_CORE_THREADCONTEXT_H


#include <mutex>
#include <thread>


namespace bmce
{


class ThreadContext
{
private:
    std::thread thread_;
    std::mutex mutex_;

    bool working_{false};

public:
    ThreadContext() = default;

    virtual ~ThreadContext()
    {
        wait();
    }

    ThreadContext(ThreadContext&& _copy) = delete;
    ThreadContext& operator=(ThreadContext&& _copy) = delete;

    ThreadContext(const ThreadContext& _copy) = delete;
    ThreadContext& operator=(const ThreadContext& _copy) = delete;

    std::thread::id threadId()
    {
        return thread_.get_id();
    }

    bool isRunning()
    {
        return thread_.joinable();
    }

    bool isWorking()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return working_;
    }

    bool isMain()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return working_ && !thread_.joinable();
    }

    void start()
    {
        innerLoop();
    }

    bool startInThread()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!thread_.joinable())
        {
            thread_ = std::thread(&ThreadContext::innerLoop, this);
            return true;
        }
        return false;
    }

    void wait()
    {
        if (thread_.joinable())
        {
            thread_.join();
        }
    }

    virtual void loop() = 0;

private:
    auto& thread()
    {
        return mutex_;
    }

    void setWorking(bool working)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        working_ = working;
    }

    void innerLoop()
    {
        setWorking(true);
        loop();
        setWorking(false);
    }

};


} // namespace bmce


#endif
