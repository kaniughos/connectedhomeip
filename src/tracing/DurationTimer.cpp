#include "DurationTimer.h"
#include <stdint.h>
#include <time.h>
#include <string>
#include <lib/support/logging/CHIPLogging.h>
//#include <system/SystemClock.h>

using namespace std;
//using chip::System;

//todo add description
namespace chip{
    namespace timing{
        /**   TimespecTimer implementations   */

        //static function
        double TimespecTimer::duration_calc(timespec start, timespec stop){
            return (stop.tv_sec - start.tv_sec)+((stop.tv_nsec - start.tv_nsec) * 1e-9);
        }

        //member functions
        void TimespecTimer::start(){
            struct timespec now;
            clock_gettime(CLOCK_REALTIME, &now);
            t1 = now;
            //todo use logging instead of stdout
            cout <<  "Timer "<< label << " start " << toTimeStr( now ) << '\n';
        }

        void TimespecTimer::stop(){
            struct timespec now;
            clock_gettime(CLOCK_REALTIME, &now) ;
            t2 = now;
            cout <<  "Timer "<< label << " stop " << toTimeStr( now ) << '\n';
            duration();
        }

        double TimespecTimer::duration(){
            double dur = duration_calc(t1,t2);
            cout <<  "Timer "<< label << " TIME_SPENT (sec) " << dur << '\n';
            return dur;
        }

        //utility method
        char* TimespecTimer::toTimeStr(timespec time){
            char buff[100];
            strftime(buff, sizeof buff, "%D %T", gmtime(&time.tv_sec) );
            char* str = new char[ sizeof buff + 1];
            //todo revisit this size
            snprintf(str, sizeof(buff)+4+21 , " %s.%09ld", buff, time.tv_nsec );
            return str;
        }


        //####  SystemClock #####
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
            chip::System::Clock::Microseconds64 now = chip::System::Clock::ClockImpl().GetMonotonicMilliseconds64();//GetMonotonicTimestamp();
            t1=now;
            string time = chip::System::Clock::ClockImpl().GetClock_RealTime( now ).AsString();
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

 /**   TimeTTimer implementations   */

        //static function - time_t is in seconds
        double TimeTTimer::duration_calc(time_t start, time_t stop){
            return (stop - start);
        }

        //member functions
        void TimeTTimer::start(){
            t1 = time(NULL);
            //todo use logging instead of stdout
            cout <<  "Timer "<< label << " start " << toTimeStr( t1 ) << '\n';
        }

        void TimeTTimer::stop(){
            t2 = time(NULL);;
            cout <<  "Timer "<< label << " stop " << toTimeStr( t2 ) << '\n';
            duration();
        }

        double TimeTTimer::duration(){
            double dur = duration_calc(t1,t2);
            cout <<  "Timer "<< label << " TIME_SPENT (sec) " << dur << '\n';
            return dur;
        }

        //utility method
        char* TimeTTimer::toTimeStr(time_t time){
            char buff[100];
            strftime(buff, sizeof buff, "%s", gmtime(&time) );
            char* str = new char[ sizeof buff + 1];
            //todo revisit this size
            snprintf(str, sizeof(buff)+4+21 , " %s  ( %jd sec.)", buff, time );

            //if(time != (time_t)(-1))
            //printf("The current time is %s(%jd seconds since the Epoch)\n",
            //   asctime(gmtime(&time)), (intmax_t)time);

            return str;
        }

        /**   TimeValTimer implementations   */

        //static function - time_t is in seconds
        double TimeValTimer::duration_calc(timeval start, timeval stop){
            return (stop.tv_sec - start.tv_sec)+((stop.tv_usec - start.tv_usec) * 1e-9);
        }

        //member functions
        void TimeValTimer::start(){
            struct timeval now;
            gettimeofday(&now,NULL);
            t1 = now;

            //todo use logging instead of stdout
            cout <<  "Timer "<< label << " start " << toTimeStr( t1 ) << '\n';
        }

        void TimeValTimer::stop(){
            struct timeval now;
            gettimeofday(&now,NULL);
            t2 = now;

            cout <<  "Timer "<< label << " stop " << toTimeStr( t2 ) << '\n';
            duration();
        }

        double TimeValTimer::duration(){
            double dur = duration_calc(t1,t2);
            cout <<  "Timer "<< label << " TIME_SPENT (sec) " << dur << '\n';
            return dur;
        }

        #define DATETIME_LEN (sizeof "1970-01-01T23:59:59.")
        #define ISO8601_LEN (sizeof "1970-01-01T23:59:59.123456Z")

        //utility method
        char* TimeValTimer::toTimeStr(timeval time){
            char buff[DATETIME_LEN];
            strftime(buff, sizeof buff, "%Y-%m-%dT%H:%M:%SZ", gmtime(&time.tv_sec) );
            char* str = new char[ sizeof buff + 1];
            snprintf(str, ISO8601_LEN , " %s.%03ld", buff, time.tv_usec );
            return str; //timeval_to_str( buff, 0, &time);
        }

        /*
        char * timeval_to_str(char iso8601[ISO8601_LEN], unsigned precision, const struct timeval * tv ) {
            struct tm tm;
            if (!gmtime_r(&tv->tv_sec, &tm))
                return memcpy(iso8601, "Error: Year overflow", sizeof "Error: Year overflow");

            tm.tm_year %= 10*1000;
            char *frac = iso8601 + strftime(iso8601, sizeof "1970-01-01T23:59:59.", "%Y-%m-%dT%H:%M:%SZ", &tm);

            if (precision) {
                unsigned long usecs = tv->tv_usec;
                for (int i = precision; i < 6; i++) usecs /= 10;
                char *spaces = frac + sprintf(frac - 1, ".%-*luZ", precision, usecs) - 3;
                if (spaces > frac) while (*spaces == ' ') *spaces-- = '0';
            }

            return iso8601;
        }
        */

        


    }

}