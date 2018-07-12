#include "core/signal.h"

#include <algorithm>

#include "core/object.h"


namespace bmce
{


SlotContext::SlotContext(SignalBase* signal, SlotId id) :
    signal_(signal),
    slot_id_(id)
{}

SignalBase* SlotContext::signal() const
{
    return signal_;
}

SlotId SlotContext::slotId() const
{
    return slot_id_;
}

void SlotContext::release()
{
    signal_->disconnect(slot_id_);
}


//-----------------------------------------------------------------------------


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


void SignalBase::registerListener(Object* listener)
{
    std::lock_guard<std::mutex> lock(mutex_);

    auto l = listeners_;
    if (std::find(l.begin(), l.end(), listener) == l.end())
    {
        listeners_.push_back(listener);
    }
}

SignalBase::~SignalBase()
{
    std::lock_guard<std::mutex> lock(mutex_);

    for (auto& object : listeners_)
    {
        object->signalDestroyed(this);
    }
}


} // namespace bmce
