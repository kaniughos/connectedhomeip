#pragma once

#include <string>

/**
 * CHIP_DEVICE_IS_ESP32
 *
 * If 1, enable then assume esp32 device.

#ifndef CHIP_DEVICE_IS_ESP32
#define CHIP_DEVICE_IS_ESP32 1
#endif
 **/

/**
 * CHIP_DEVICE_IS_NRF
 *
 * If 1, enable then assume nRF device.
 */

#ifndef CHIP_DEVICE_IS_NRF
#define CHIP_DEVICE_IS_NRF 1
#endif

using namespace std;


// todo add description
namespace chip {
namespace timing {

class GenericTimer
{
public:
    virtual ~GenericTimer();
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
    //uint8_t module;

public:
    // constructors
    /*DurationTimer(uint8_t mod, string s) : GenericTimer{}
    {
        module = mod;
        label  = s;
    }*/
    DurationTimer(string s) : GenericTimer{} { label = s; }
    virtual ~DurationTimer() = default;
    virtual void start() override = 0;
    virtual void stop() override = 0;
    /*{
        // GenericTimer::stop();
        destroy();

        delete this;
    };*/
    virtual double duration() override = 0;

    virtual void destroy() override = 0;

    double duration_calc(T start, T stop);

};

GenericTimer GetDefaultTimingInstance(char label);
GenericTimer * GetDefaultTimingInstancePtr(string label);

} // namespace timing
} // namespace chip
