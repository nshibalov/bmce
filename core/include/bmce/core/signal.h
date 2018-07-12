#ifndef BMCE_CORE_SIGNAL_H
#define BMCE_CORE_SIGNAL_H


#include <functional>
#include <map>
#include <mutex>
#include <vector>


namespace bmce
{


using SlotId = unsigned int;


class Object;
class SignalBase;


class SlotContext
{
private:
    SignalBase* signal_{nullptr};
    SlotId slot_id_{0};

public:
    SlotContext(SignalBase* signal, SlotId id);
    SignalBase* signal() const;
    SlotId slotId() const;
    void release();
};


class SignalBase
{
private:
    std::mutex mutex_;
    std::vector<Object*> listeners_;
    SlotId next_slot_id_ {0};

public:
    SignalBase() = default;
    virtual ~SignalBase();

    SignalBase(SignalBase&& from) = delete;
    SignalBase& operator=(SignalBase&& rhs) = delete;

    SignalBase(const SignalBase& from) = delete;
    SignalBase& operator=(const SignalBase& rhs) = delete;

    void registerListener(Object* listener);
    virtual void disconnect(SlotId id) = 0;

protected:
    std::mutex& mutex();
    void setSlotId(SlotId id);
    SlotId nextSlotId();
};


template<typename ...ARGS>
class Signal : public SignalBase
{
public:
    using Slot = std::function<void(ARGS...)>;
    using NoArgSlot = std::function<void()>;

    using Slots = std::map<SlotId, Slot>;
    using NoArgSlots = std::map<SlotId, NoArgSlot>;

private:
    Slots slots_;
    NoArgSlots na_slots_;

public:
    SlotContext connect(const Slot& slot)
    {
        std::lock_guard<std::mutex> lock(mutex());

        auto slot_id = nextSlotId();
        slots_.insert(std::make_pair(slot_id, slot));
        return {this, slot_id};
    }

    SlotContext connect(const NoArgSlot& slot)
    {
        std::lock_guard<std::mutex> lock(mutex());

        auto slot_id = nextSlotId();
        na_slots_.insert(std::make_pair(slot_id, slot));
        return {this, slot_id};
    }

    template<typename T>
    SlotContext connect(void(T::*func)(ARGS...), T* inst)
    {
        return connect([=](ARGS&&... args)
        {
            (inst->*func)(std::forward<ARGS>(args)...);
        });
    }

    template<typename T>
    SlotContext connect(void(T::*func)(), T* inst)
    {
        return connect([func, inst]() { (inst->*func)(); });
    }

    void disconnect(SlotId id) override
    {
        std::lock_guard<std::mutex> lock(mutex());

        slots_.erase(id);
        na_slots_.erase(id);
    }

    void reset()
    {
        std::lock_guard<std::mutex> lock(mutex());

        slots_.clear();
        na_slots_.clear();

        setSlotId(0);
    }

    void emit(ARGS... args)
    {
        std::lock_guard<std::mutex> lock(mutex());

        for (auto& it : slots_)
        {
            it.second(std::forward<ARGS>(args)...);
        }

        for (auto& it : na_slots_)
        {
            it.second();
        }
    }

};


template<>
class Signal<> : public SignalBase
{
public:
    using Slot = std::function<void()>;
    using Slots = std::map<SlotId, Slot>;

private:
    Slots slots_;

public:
    SlotContext connect(const Slot& slot)
    {
        std::lock_guard<std::mutex> lock(mutex());

        auto slot_id = nextSlotId();
        slots_.insert(std::make_pair(slot_id, slot));
        return {this, slot_id};
    }

    template<typename T>
    SlotContext connect(void(T::*func)(), T* inst)
    {
        return connect([func, inst]() { (inst->*func)(); });
    }

    void disconnect(SlotId id) override
    {
        std::lock_guard<std::mutex> lock(mutex());

        slots_.erase(id);
    }

    void reset()
    {
        std::lock_guard<std::mutex> lock(mutex());

        slots_.clear();

        setSlotId(0);
    }

    void emit()
    {
        std::lock_guard<std::mutex> lock(mutex());

        for (auto& it : slots_)
        {
            it.second();
        }
    }

};


} // namespace bmce


#endif
