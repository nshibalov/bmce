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
    std::mutex mutex_;
    SlotId next_slot_id_ {0};

    std::map<SignalTarget*, SlotIdList> target_slots_;

public:
    SignalBase() = default;
    virtual ~SignalBase();

    SignalBase(SignalBase&& from) = delete;
    SignalBase& operator=(SignalBase&& rhs) = delete;

    SignalBase(const SignalBase& from) = delete;
    SignalBase& operator=(const SignalBase& rhs) = delete;

    virtual void disconnect(SlotId id) = 0;

    void targetDestroyed(SignalTarget* target);

protected:
    std::mutex& mutex();
    void setSlotId(SlotId id);
    SlotId nextSlotId();
    void addTargetSlot(SignalTarget*, SlotId id);
    void removeTargetSlot(SignalTarget*, SlotId id);
    void removeTargetSlots(SignalTarget*);
};


} // namespace bmce


#endif
