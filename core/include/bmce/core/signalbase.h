#ifndef BMCE_CORE_SIGNALBASE_H
#define BMCE_CORE_SIGNALBASE_H


#include <map>
#include <mutex>

#include "core/slot.h"


namespace bmce
{


class SignalTarget;


class SignalBase
{
private:
    SlotId next_slot_id_ {0};

    std::map<SignalTarget*, SlotIdList> target_slots_;

public:
    SignalBase() = default;
    virtual ~SignalBase();

    SignalBase(SignalBase&& o) = delete;
    SignalBase& operator=(SignalBase&& rhs) = delete;

    SignalBase(const SignalBase& o) = delete;
    SignalBase& operator=(const SignalBase& rhs) = delete;

    virtual void disconnect(SlotId id) = 0;

    void targetDestroyed(SignalTarget* target);

protected:
    mutable std::mutex mutex_;

protected:
    void setSlotId(SlotId id);
    SlotId nextSlotId();
    void addTargetSlot(SignalTarget*, SlotId id);
    void addTargetSlot(void*, SlotId id);
    void removeTargetSlot(SignalTarget*, SlotId id);
    void removeTargetSlots(SignalTarget*);
};


} // namespace bmce


#endif
