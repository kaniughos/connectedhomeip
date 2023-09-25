#include "DurationTimer.h"
#include "DurationTimerImpl.h"
//#include <lib/support/logging/CHIPLogging.h>
#include <stdint.h>
#include <string>
//#include <time.h>
//#include <sys/time.h>
// #include <system/SystemClock.h>

using namespace std;
// using chip::System;

// todo add description
namespace chip {
namespace timing {
    
GenericTimer GetDefaultTimingInstance(string label)
{
    #ifdef CHIP_DEVICE_IS_ESP32
        return chip::timing::TimespecTimer(label);
    #elseif CHIP_DEVICE_IS_NRF
        return chip::timing::TimeValTimer(label);  
    #elseif CHIP_DEVICE_IS_ESP32_2
        return chip::timing::TimeTTimer(label);   
    #else
        return chip::timing::TimeValTimer(label);      
    #endif
}

GenericTimer * GetDefaultTimingInstancePtr(string label)
{

    #ifdef CHIP_DEVICE_IS_ESP32
        return new chip::timing::TimespecTimer(label);
    #elseif CHIP_DEVICE_IS_NRF
        return new chip::timing::TimeValTimer(label);   
    #elseif CHIP_DEVICE_IS_ESP32_2 
        return new chip::timing::TimeTTimer(label);  
    #else
        return new chip::timing::TimeValTimer(label);         
    #endif
}


//DurationTimer::~DurationTimer(){}
GenericTimer::~GenericTimer(){}
//DurationTimer::~GenericTimer(){}
//



} // namespace timing

} // namespace chip