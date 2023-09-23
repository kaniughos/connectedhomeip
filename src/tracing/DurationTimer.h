#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <sys/time.h>
#include <time.h>

using namespace std;

// todo add description
namespace chip {
namespace timing {

class GenericTimer
{
public:
    virtual ~GenericTimer() = default;
    virtual void start();
    virtual void stop();
    virtual double duration();
    virtual void destroy();
};

template <typename T>
class DurationTimer : public GenericTimer
{
protected:
    T t1;
    T t2;
    string label;
    // todo revisit module references
    uint8_t module;

public:
    // constructors
    DurationTimer(uint8_t mod, string s) : GenericTimer{}
    {
        module = mod;
        label  = s;
    }
    DurationTimer(string s) : GenericTimer{} { label = s; }
    virtual ~DurationTimer()      = default;
    virtual void start() override = 0;
    virtual void stop() override
    {
        // GenericTimer::stop();
        destroy();

        delete this;
    };
    virtual double duration() override = 0;

    virtual void destroy() override = 0;

    static double duration_calc(T start, T stop);
    // DurationTimer static getInstance(string s);
};

GenericTimer GetDefaultTimingInstance(string label);
GenericTimer * GetDefaultTimingInstancePtr(string label);

} // namespace timing
} // namespace chip
