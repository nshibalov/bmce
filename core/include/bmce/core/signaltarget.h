#ifndef BMCE_CORE_SIGNALTARGET_H
#define BMCE_CORE_SIGNALTARGET_H


#include <vector>


namespace bmce
{


class SignalBase;


class SignalTarget
{
private:
    std::vector<SignalBase*> signals_;

public:
    SignalTarget() = default;
    virtual ~SignalTarget();

    SignalTarget(SignalTarget&& from) = default;
    SignalTarget& operator=(SignalTarget&& rhs) = default;

    SignalTarget(const SignalTarget& from) = default;
    SignalTarget& operator=(const SignalTarget& rhs) = default;

    void addSignal(SignalBase* signal);
    void removeSignal(SignalBase* signal);

};


} // namespace bmce


#endif
