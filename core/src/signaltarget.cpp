#include "core/signaltarget.h"


#include <algorithm>

#include "core/log/log.h"
#include "core/signalbase.h"


namespace bmce
{


SignalTarget::~SignalTarget()
{
    BMCE_INFO("~SignalTarget")
    for (auto& signal : signals_)
    {
        signal->targetDestroyed(this);
    }
    signals_.clear();
}


void SignalTarget::addSignal(SignalBase* signal)
{
    BMCE_INFO("addSignal")
    auto& l = signals_;
    if (std::find(l.begin(), l.end(), signal) == l.end())
    {
        signals_.push_back(signal);
    }
}


void SignalTarget::removeSignal(SignalBase* signal)
{
    BMCE_INFO("removeSignal")
    auto& l = signals_;
    l.erase(std::remove(l.begin(), l.end(), signal), l.end());
}


} // namespace bmce

