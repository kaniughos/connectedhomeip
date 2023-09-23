#include "DurationTimer.h"
#include "DurationTimerImpl.h"
#include <lib/support/logging/CHIPLogging.h>
#include <stdint.h>
#include <string>
#include <time.h>
// #include <system/SystemClock.h>

using namespace std;
// using chip::System;

// todo add description
namespace chip {
namespace timing {

//GenericTimer::~GenericTimer(){};
//DurationTimer::~DurationTimer(){};

GenericTimer GetDefaultTimingInstance(string label)
{
   // return chip::timing::TimespecTimer(label);
   return chip::timing::TimeValTimer(label);
}

GenericTimer * GetDefaultTimingInstancePtr(string label)
{
    /*chip::timing::TimespecTimer val = new chip::timing::TimespecTimer(label);
    // chip::timing::TimeValTimer val = new chip::timing::TimeValTimer(label);
    chip::timing::GenericTimer * ptr;
    ptr = &val;
    return ptr;*/

    //return new chip::timing::TimespecTimer(label);
    return new chip::timing::TimeValTimer(label);
}

} // namespace timing

} // namespace chip