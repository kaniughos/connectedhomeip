#pragma once

#include <string>

#include <system/SystemConfig.h>

/**
 * @file
 * 
 *  Uses SystemClock.h HAVE_CLOCK_GETTIME to determine board type i.e. esp32 or nRF etc.
 *  CHIP_DEVICE_USES_SYS_TIME flag indicates nRF board whose clock implementation is available in Syste,Clock.h.
 *  CHIP_DEVICE_USES_TIME_H flag for esp32 uses a time.h timespec
 */

#if (CHIP_SYSTEM_CONFIG_PLATFORM_PROVIDES_TIME && (CHIP_SYSTEM_CONFIG_USE_POSIX_TIME_FUNCTS || CHIP_SYSTEM_CONFIG_USE_SOCKETS))
#define CHIP_DEVICE_USES_SYS_TIME 1
#define CHIP_DEVICE_USES_TIME_H 0
#else // ! CHIP_SYSTEM_CONFIG_PLATFORM_PROVIDES_TIME etal
#define CHIP_DEVICE_USES_TIME_H 1
#define CHIP_DEVICE_USES_SYS_TIME 0
#endif // CHIP_SYSTEM_CONFIG_PLATFORM_PROVIDES_TIME etal


#if CHIP_DEVICE_USES_SYS_TIME
/**
 * Use SystemClock/clock-gettime  
 * */
#include <system/SystemClock.h>
#endif

#if CHIP_DEVICE_USES_TIME_H
/**
 * SystemClock/clock-gettime not supported therefore use time.h
 * */
#include <time.h>
#endif

using namespace std;

namespace chip {
namespace timing {

class DurationTimer
{
#if CHIP_DEVICE_USES_SYS_TIME
/**
 * SystemClock/clock-gettime supported therefore timeval struct.
 * */
private:
    string toTimeStr(timeval * time);

protected:
    timeval t1;
    timeval t2;
    string label;
#endif

#if CHIP_DEVICE_USES_TIME_H
/**
 * clock-SystemClock/clock-gettime not supported therefore use timespec struct
 * */
private:
    string toTimeStr(timespec * time);

protected:
    timespec t1;
    timespec t2;
    string label;
#endif


public:
    // constructor
    /**
     * Constructor sets label as an identifier of a unique process.
    */
    DurationTimer(string s) { label = s; }

    //default destructor
    ~DurationTimer() = default;

    // member functions
    /** 
     * Sets t1 as start time.
     * */
    void start();

    /** 
     * Sets t2 as stop time.
     * */
    void stop();

    /** 
     * Calculates difference between t2 and t1.
     * */
    double duration();
};

DurationTimer GetDefaultTimingInstance(string label);
DurationTimer * GetDefaultTimingInstancePtr(string label);

} // namespace timing
} // namespace chip