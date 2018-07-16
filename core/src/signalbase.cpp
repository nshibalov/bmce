#include "core/signalbase.h"


#include <algorithm>

#include "core/log/log.h"
#include "core/signaltarget.h"


namespace bmce
{


SignalBase::~SignalBase()
{
    BMCE_INFO("~SignalBase")

    for (auto& it : target_slots_)
    {
        it.first->removeSignal(this);
    }
}


std::mutex& SignalBase::mutex()
{
    return mutex_;
}


SlotId SignalBase::nextSlotId()
{
    return next_slot_id_++;
}


void SignalBase::setSlotId(SlotId id)
{
    next_slot_id_ = id;
}


void SignalBase::targetDestroyed(SignalTarget* target)
{
    BMCE_INFO("targetDestroyed")
    removeTargetSlots(target);
}

void SignalBase::addTargetSlot(SignalTarget* target, SlotId id)
{
    BMCE_INFO("addTargetSlot")
    auto it = target_slots_.insert(std::make_pair(target, id));

    auto& slots = it.first->second;
    if (std::find(slots.begin(), slots.end(), id) == slots.end())
    {
        slots.push_back(id);
    }

    target->addSignal(this);
}

void SignalBase::removeTargetSlot(SignalTarget* target, SlotId id)
{
    BMCE_INFO("removeTargetSlot")
    auto it = target_slots_.find(target);
    if (it != target_slots_.end())
    {
        auto& slots = it->second;
        slots.erase(std::remove(slots.begin(), slots.end(), id), slots.end());
    }
}

void SignalBase::removeTargetSlots(SignalTarget* target)
{
    BMCE_INFO("removeTargetSlots")
    target_slots_.erase(target);
}


} // namespace bmce
