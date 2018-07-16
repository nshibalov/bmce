#ifndef BMCE_CORE_SIGNAL_H
#define BMCE_CORE_SIGNAL_H


#include <functional>
#include <map>
#include <mutex>
#include <vector>

#include "core/log/log.h"
#include "core/signalbase.h"
#include "core/signaltarget.h"
#include "core/slot.h"


namespace bmce
{


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
    SlotId connect(const Slot& slot)
    {
        std::lock_guard<std::mutex> lock(mutex());

        auto slot_id = nextSlotId();
        slots_.insert(std::make_pair(slot_id, slot));
        return slot_id;
    }

    SlotId connect(const NoArgSlot& slot)
    {
        std::lock_guard<std::mutex> lock(mutex());

        auto slot_id = nextSlotId();
        na_slots_.insert(std::make_pair(slot_id, slot));
        return slot_id;
    }

    template<typename T>
    SlotId connect(void(T::*slot)(ARGS...), T* inst)
    {
        SlotId id = connect([=](ARGS&&... args)
        {
            (inst->*slot)(std::forward<ARGS>(args)...);
        });

        BMCE_INFO("connect")
        addTargetSlot(inst, id);

        return id;
    }

    template<typename T>
    SlotId connect(void(T::*slot)(), T* inst)
    {
        SlotId id = connect([slot, inst]() { (inst->*slot)(); });
        BMCE_INFO("connect")
        addTargetSlot(inst, id);
        return id;
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

        for (auto& it : slots_) { it.second(std::forward<ARGS>(args)...); }
        for (auto& it : na_slots_) { it.second(); }
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
    SlotId connect(const Slot& slot)
    {
        std::lock_guard<std::mutex> lock(mutex());

        auto slot_id = nextSlotId();
        slots_.insert(std::make_pair(slot_id, slot));
        return slot_id;
    }

    template<typename T>
    SlotId connect(void(T::*slot)(), T* inst)
    {
        SlotId id = connect([slot, inst]() { (inst->*slot)(); });
        BMCE_INFO("connect")
        addTargetSlot(inst, id);
        return id;
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

        for (auto& it : slots_) { it.second(); }
    }

};


} // namespace bmce


#endif
