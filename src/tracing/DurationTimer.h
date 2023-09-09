#pragma once

#include <string>
#include <time.h>
#include <iostream>

using namespace std;
//using namespace chip::Logging;

namespace chip{

    namespace timing{
        
        template <typename T>
        class DurationTimer{
            protected:
                T t1;
                T t2;
                string label;
            public:    
                DurationTimer(string s ){
                   label = s;
                }
                void start();
                void stop();
                double duration(); 
                static double duration_calc(T start, T stop); 
        };

        class TimespecTimer : public DurationTimer<timespec>{
                //char * module;
                public:
                    TimespecTimer( string s ): DurationTimer(s){}
                    //member functions
                    void start(){
                        struct timespec now;
                        clock_gettime(CLOCK_REALTIME, &now) ;
                        t1 = now;
                        //ChipLogProgress(module, " %ld.%09ld KN "+label+" ", now.tv_sec,now.tv_nsec);
                        //ChipLogAutomation( " %ld.%09ld KN "+label+" ", now.tv_sec,now.tv_nsec);
                        cout <<  "KN "<< label << "start sec" << now.tv_sec<<","<<now.tv_nsec << '\n';
                    }

                    void stop(){
                        struct timespec now;
                        clock_gettime(CLOCK_REALTIME, &now) ;
                        t2 = now;
                        //ChipLogProgress(module, " %ld.%09ld KN "+label+" ", now.tv_sec,now.tv_nsec);
                        //ChipLogAutomation( " %ld.%09ld KN "+label+" ", now.tv_sec,now.tv_nsec);
                        cout <<  "KN "<< label << "stop sec" << now.tv_sec<<","<<now.tv_nsec << '\n';
                        duration();
                    }

                    double duration(){
                        double dur = duration_calc(t1,t2);
                        //ChipLogProgress(module, "KN "+label+" TIME_SPENT (sec) %lf", dur);
                        //ChipLogAutomation("KN "+label+" TIME_SPENT (sec) %lf", dur);
                        cout <<  "KN "<< label << " TIME_SPENT (sec) " << dur << '\n';
                        return dur;
                    }

                    double static duration_calc(timespec start, timespec stop);
        };

    }
}