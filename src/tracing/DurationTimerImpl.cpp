#include "DurationTimerImpl.h"
#include "DurationTimer.h"
//#include <string>
#include <cstring>

#ifdef CHIP_DEVICE_IS_NRF
#include <sys/time.h>
#endif

#if defined  (CHIP_DEVICE_IS_ESP32) || defined (CHIP_DEVICE_IS_ESP32_2)
#include <time.h>
#endif

using namespace std;

// todo add description
namespace chip {
namespace timing {

// ####  SystemClock #####
/**
//static function
double SystemClockTimer::duration_calc(chip::System::Clock::Timestamp start, chip::System::Clock::Timestamp stop){
    return (stop.max() - start.max());
}

//member functions
void SystemClockTimer::start(){
    //struct timespec now;
    //clock_gettime(CLOCK_REALTIME, &now);
    //t1 = chip::System::Clock::ClockImpl().GetMonotonicMilliseconds64();
    chip::System::Clock::Microseconds64 now =
chip::System::Clock::ClockImpl().GetMonotonicMilliseconds64();//GetMonotonicTimestamp(); t1=now; string time =
chip::System::Clock::ClockImpl().GetClock_RealTime( now ).AsString();
    //todo use logging instead of stdout
    cout <<  "Timer "<< label << " start " << time << '\n';
}

void SystemClockTimer::stop(){
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now) ;
    t2 = chip::System::Clock::ClockImpl().GetMonotonicTimestamp();
    cout <<  "Timer "<< label << " stop " << toTimeStr( now ) << '\n';
    duration();
}

double SystemClockTimer::duration(){
    double dur = duration_calc(t1,t2);
    cout <<  "Timer "<< label << " TIME_SPENT (sec) " << dur << '\n';
    return dur;
}

DurationTimer<chip::System::Clock::Timestamp> GetSystemClockTimingInstance(string label){
    return chip::timing::SystemClockTimer(label);
}
*/

#ifdef CHIP_DEVICE_IS_ESP32_2
/**   TimeTTimer implementations   */

// static function - time_t is in seconds
double TimeTTimer::duration_calc(time_t start, time_t stop)
{
    return (stop - start);
}

// member functions
void TimeTTimer::start()
{
    t1 = time(NULL);
    // todo use logging instead of stdout
    cout << "Timer " << label << " start " << toTimeStr(t1) << '\n';
}

void TimeTTimer::stop()
{
    t2 = time(NULL);
    cout << "Timer " << label << " stop " << toTimeStr(t2) << '\n';
    duration();
    // delete?
}

double TimeTTimer::duration()
{
    double dur = duration_calc(t1, t2);
    cout << "Timer " << label << " TIME_SPENT (sec) " << dur << '\n';
    return dur;
}

// utility method
char * TimeTTimer::toTimeStr(time_t time)
{
    char buff[DATETIME_LEN];
    strftime(buff, DATETIME_LEN, DATETIME_PATTERN, gmtime(&time));

    return buff;
}

//TimeTTimer::~TimeTTimer(){}
#endif

/**   TimeValTimer implementations   */
#ifdef CHIP_DEVICE_IS_NRF
// static function - time_t is in seconds
double TimeValTimer::duration_calc(timeval start, timeval stop)
{
    return (stop.tv_sec - start.tv_sec) + ((stop.tv_usec - start.tv_usec) * 1e-5);
}

// member functions
void TimeValTimer::start()
{
    //struct timeval now;
    gettimeofday(&t1, NULL);
    // todo use logging instead of stdout
    cout << "Timer " << label << " start " << toTimeStr(t1) << '\n';
}

void TimeValTimer::stop()
{
    gettimeofday(&t2, NULL);
    cout << "Timer " << label << " stop " << toTimeStr(t2) << '\n';
    duration();
}

double TimeValTimer::duration()
{
    double dur = duration_calc(t1, t2);
    cout << "Timer " << label << " TIME_SPENT (sec) " << dur << '\n';
    //string timestr = toTimeStr(t2);
    //printf( "Timer: %s TIME_SPENT (sec) %f , time: %s ", label.c_str(), dur, timestr.c_str());
    return dur;
}

// utility method
char * TimeValTimer::toTimeStr(timeval time)
{
    char buff[DATETIME_LEN];
    strftime(buff, DATETIME_LEN, DATETIME_PATTERN, gmtime(&time.tv_sec));
    char * str = new char[ISO8601_LEN];
    snprintf(str, ISO8601_LEN, " %s.%05ld", buff, time.tv_usec);
    
    return str; 
    /*
    char * str = new char[DATETIME_LEN];
    memcpy(str,"1970-01-01T23:59:59Z",DATETIME_LEN);
    printf("printf -> The current time is %s \n",str);
    str[DATETIME_LEN] = 0; //non null terminated
    return str;
    */
}

//TimeValTimer::~TimeValTimer(){}

#endif


/**   TimespecTimer implementations   */
#ifdef CHIP_DEVICE_IS_ESP32

// static function
double TimespecTimer::duration_calc(timespec start, timespec stop)
{
    return (stop.tv_sec - start.tv_sec) + ((stop.tv_nsec - start.tv_nsec) * 1e-9);
}

// member functions
void TimespecTimer::start()
{
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    t1 = now;
    // todo use logging instead of stdout
    cout << "Timer " << label << " start " << toTimeStr(now) << '\n';
}

void TimespecTimer::stop()
{
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    t2 = now;
    cout << "Timer " << label << " stop " << toTimeStr(now) << '\n';
    duration();
}

double TimespecTimer::duration()
{
    double dur = duration_calc(t1, t2);
    cout << "Timer " << label << " TIME_SPENT (sec) " << dur << '\n';
    return dur;
}

// utility method
char * TimespecTimer::toTimeStr(timespec time)
{
    char buff[DATETIME_LEN];
    strftime(buff, DATETIME_LEN, DATETIME_PATTERN, gmtime(&time.tv_sec));
    char * str = new char[ISO8601_LEN];
    // todo revisit this size
    snprintf(str, ISO8601_LEN , " %s.%05ld", buff, time.tv_nsec);
    return str;
}

//TimespecTimer::~TimespecTimer(){}

#endif

} // namespace timing

} // namespace chip