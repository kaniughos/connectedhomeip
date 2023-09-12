#pragma once

#include <string>
#include <cstring>
#include <time.h>
#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <lib/support/logging/CHIPLogging.h>

using namespace std;

namespace chip{

    namespace timing{
        
        template <typename T>
        class DurationTimer{
            protected:
                T t1;
                T t2;
                string label;
                //LogModule module;
                uint8_t *module;
            public:    
                DurationTimer(uint8_t *mod, string s ){
                   module = mod;
                   label = s;
                }
                DurationTimer(string s ){
                   label = s;
                }
                void start();
                void stop();
                double duration(); 
                static double duration_calc(T start, T stop); 
        };

        class TimespecTimer : public DurationTimer<timespec>{
                
                protected:
                  
                    char* toTimeStr(timespec time){
                        
                        char buff[100];
                        strftime(buff, sizeof buff, "%D %T", gmtime(&time.tv_sec) );
                        char* str = new char[ sizeof buff + 1];
                        //todo revisit this size
                        snprintf(str, sizeof(buff)+4+21 , " %s.%09ld", buff, time.tv_nsec );
                        return str;
                    }

                public:
                    TimespecTimer(uint8_t *mod, string s ):  DurationTimer(mod, s){} ;
                    TimespecTimer( string s ): DurationTimer(s){};
                    //member functions
                    void start(){
                        struct timespec now;
                        clock_gettime(CLOCK_REALTIME, &now) ;
                        
                        t1 = now;
                        //ChipLogProgress(module, " %ld.%09ld KN "+label+" ", now.tv_sec,now.tv_nsec);
                        //ChipLogAutomation( " %ld.%09ld KN "+label+" ", now.tv_sec,now.tv_nsec);
                        //ChipLogAutomation( " %s KN "+label+" ", toTimeStr( now ) );
                        cout <<  "KN "<< label << " start (sec) " << toTimeStr( now ) << '\n';

                    }

                    void stop(){
                        struct timespec now;
                        clock_gettime(CLOCK_REALTIME, &now) ;
                        t2 = now;
                        //ChipLogProgress(module, " %ld.%09ld KN "+label+" ", now.tv_sec,now.tv_nsec);
                        //ChipLogAutomation( " %ld.%09ld KN "+label+" ", now.tv_sec,now.tv_nsec);
                        //cout <<  "KN "<< label << " stop (sec) " << strftime(buff, sizeof buff, "%D %T", gmtime(&now.tv_sec)) << '\n';
                        cout <<  "KN "<< label << " stop (sec) " << toTimeStr( now ) << '\n';
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