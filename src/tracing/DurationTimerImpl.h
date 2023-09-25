#pragma once

#include "DurationTimer.h"
#include <iostream>
#include <stdio.h>
#include <string>
// #include <system/SystemClock.h>
// timeval
#include <sys/time.h>
#include <time.h>

using namespace std;

// todo add description
namespace chip {
namespace timing {

#ifdef CHIP_DEVICE_IS_ESP32
// todo add description
class TimespecTimer : public DurationTimer<timespec>
{

private:
    char * toTimeStr(timespec time);

public:
    // constructors
    //TimespecTimer(uint8_t mod, string s) : DurationTimer(mod, s){};
    TimespecTimer(string s) : DurationTimer(s){};
    ~TimespecTimer();

    // member functions
    void start() override;
    void stop() override;
    double duration() override;
    double static duration_calc(timespec start, timespec stop);
    // TempTimer<timespec> static getInstance(string s){
    //     return TimespecTimer(s);
    // };
    void destroy() override
    {
        t1    = (timespec){ 0, 0 };
        t2    = (timespec){ 0, 0 };
        label = string(NULL);
    };
};

#endif

#ifdef CHIP_DEVICE_IS_ESP32_2
// todo add description
class TimeTTimer : public DurationTimer<time_t>
{

private:
    char * toTimeStr(time_t time);

public:
    // constructors
    //TimeTTimer(uint8_t mod, string s) : DurationTimer(mod, s){};
    TimeTTimer(string s) : DurationTimer(s){};
    ~TimeTTimer() ;
    // member functions
    void start();
    void stop();
    double duration();
    double static duration_calc(time_t start, time_t stop);
    // DurationTimer<time_t> getInstance(string s){
    //     return new TimeTTimer(s);
    // };
    void destroy() override
    {
        t1    = (time_t)(-1);
        t2    = (time_t)(-1);
        label = string(NULL);
    };
};

#endif

#ifdef CHIP_DEVICE_IS_NRF
// todo add description
class TimeValTimer : public DurationTimer<timeval>
{

private:
    char * toTimeStr(timeval time);

public:
    // constructors
    //TimeValTimer(uint8_t mod, string s) : DurationTimer(mod, s){};
    TimeValTimer(string s) : DurationTimer(s){};
    ~TimeValTimer();
    // member functions
    void start();
    void stop();
    double duration();
    double static duration_calc(timeval start, timeval stop);

    // DurationTimer<timeval> static getInstance(string s){
    //     return TimeValTimer(s);
    // };
    void destroy() override
    {
        t1    = ( timeval){-1};
        t2    = ( timeval){-1};
        label = string(NULL);
    };
};

#endif
// todo add description
/**
    class SystemClockTimer : public DurationTimer<chip::System::Clock::Timestamp>{

            private:
                char* toTimeStr(chip::System::Clock::Timestamp time);

            public:
                //constructors
                SystemClockTimer(uint8_t mod, string s ):  DurationTimer(mod, s){};
                SystemClockTimer( string s ): DurationTimer(s){};
                //member functions
                void start();
                void stop();
                double duration();
                double static duration_calc(chip::System::Clock::Timestamp start, chip::System::Clock::Timestamp stop);

                DurationTimer<chip::System::Clock::Timestamp> static getInstance(string s){
                    return SystemClockTimer(s);
                };

    };

    DurationTimer<chip::System::Clock::Timestamp> GetSystemClockTimingInstance(string label){}
*/

/*
 DurationTimer<timespec> GetTimespecTimingInstance(string label){
     return chip::timing::TimespecTimer(label);
 }

DurationTimer<time_t> GetTimeTTimingInstance(string label){

     return chip::timing::TimeTTimer(label);
}

DurationTimer<timeval> GetTimeValTimingInstance(string label){

     return chip::timing::TimeValTimer(label);
}

 template <typename T>
 DurationTimer<T> GetGenericTimingInstance(string label){
     //return GetSystemClockTimingInstance(label);
     return GetTimeTTimingInstance(label);
 }
 */

} // namespace timing
} // namespace chip
