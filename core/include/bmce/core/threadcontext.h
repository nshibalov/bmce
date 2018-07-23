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
    mutable std::mutex mutex_;

    bool working_{false};

public:
    ThreadContext() = default;

    virtual ~ThreadContext()
    {
        wait();
    }

    ThreadContext(ThreadContext&& o) = delete;
    ThreadContext& operator=(ThreadContext&& rhs) = delete;

    ThreadContext(const ThreadContext& o) = delete;
    ThreadContext& operator=(const ThreadContext& rhs) = delete;

    std::thread::id threadId()
    {
        return thread_.get_id();
    }

    bool isRunning() const
    {
        return thread_.joinable();
    }

    bool isWorking() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return working_;
    }

    bool isMain() const
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

    virtual void run() = 0;

private:
    void setWorking(bool working)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        working_ = working;
    }

    void innerLoop()
    {
        setWorking(true);
        run();
        setWorking(false);
    }

};


} // namespace bmce


#endif
