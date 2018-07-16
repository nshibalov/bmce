#ifndef BMCE_CORE_OBJECT_H
#define BMCE_CORE_OBJECT_H


#include <algorithm>
#include <mutex>
#include <vector>

#include "core/log/log.h"
#include "core/signal.h"
#include "core/signaltarget.h"


namespace bmce
{


class Object : public SignalTarget
{
};


} // namespace bmce


#endif
