#ifndef BMCE_CORE_OBJECT_H
#define BMCE_CORE_OBJECT_H


#include <algorithm>
#include <vector>

#include "core/log/log.h"
#include "core/signal.h"


namespace bmce
{


class Object
{
private:
    std::vector<SlotContext> slot_contexts_;

public:
    Object() = default;
    virtual ~Object()
    {
        releaseSlots();
    };

    Object(Object&& from) = delete;
    Object& operator=(Object&& rhs) = delete;

    Object(const Object& from) = delete;
    Object& operator=(const Object& rhs) = delete;

    void slot(const SlotContext& slot_context)
    {
        slot_context.signal()->registerListener(this);

        slot_contexts_.push_back(slot_context);
    }

    void signalDestroyed(SignalBase* signal)
    {
        auto it = std::remove_if(slot_contexts_.begin(), slot_contexts_.end(),
        [signal](const SlotContext& slot_context)
        {
            return slot_context.signal() == signal;
        });
        slot_contexts_.erase(it, slot_contexts_.end());
    }

protected:
    void releaseSlots()
    {
        for (auto& slot_context : slot_contexts_)
        {
            slot_context.release();
        }
        slot_contexts_.clear();
    }

};


} // namespace bmce


#endif
