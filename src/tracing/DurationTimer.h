#pragma once

#include <string>
#include <time.h>
#include <iostream>
#include <stdio.h>
//#include <system/SystemClock.h>
//timeval
#include <sys/time.h>

using namespace std;

//todo add description
namespace chip{
    namespace timing{
        
        class GenericTimer{
            public: 
               void start();
               void stop();
               double duration(); 
        };

        template <typename T>
        class DurationTimer : public GenericTimer{
            protected:
                T t1;
                T t2;
                string label;
                //todo revisit module references
                uint8_t module;
            public:    
                //constructors
                DurationTimer(uint8_t mod, string s ){
                   module = mod;
                   label = s;
                }
                DurationTimer(string s ){
                   label = s;
                }
                //void start();
                //void stop();
                //double duration(); 
                void destruct(){
                        t1 = NULL;
                        t2 = NULL;
                        label = NULL;
                    };
                static double duration_calc(T start, T stop); 
                //DurationTimer static getInstance(string s);
        };

        //todo add description
        class TimespecTimer : public DurationTimer<timespec>{
                
                private:
                    char* toTimeStr(timespec time);

                public:
                    //constructors
                    TimespecTimer(uint8_t mod, string s ):  DurationTimer(mod, s){};
                    TimespecTimer( string s ): DurationTimer(s){};

                    //member functions
                    void start();
                    void stop();
                    double duration(); 
                    double static duration_calc(timespec start, timespec stop);
                    DurationTimer<timespec> static getInstance(string s){
                        return TimespecTimer(s);
                    };
        };

        //todo add description
        class TimeTTimer : public DurationTimer<time_t>{
                
                private:
                    char* toTimeStr(time_t time);

                public:
                    //constructors
                    TimeTTimer(uint8_t mod, string s ):  DurationTimer(mod, s){};
                    TimeTTimer( string s ): DurationTimer(s){};

                    //member functions
                    void start();
                    void stop();
                    double duration(); 
                    double static duration_calc(time_t start, time_t stop);
                    DurationTimer<time_t> static getInstance(string s){
                        return TimeTTimer(s);
                    };
        };
            
        //todo add description
        class TimeValTimer : public DurationTimer<timeval>{
                
                private:
                    char* toTimeStr(timeval time);

                public:
                    //constructors
                    TimeValTimer(uint8_t mod, string s ):  DurationTimer(mod, s){};
                    TimeValTimer( string s ): DurationTimer(s){};
                    //member functions
                    void start();
                    void stop();
                    double duration(); 
                    double static duration_calc(timeval start, timeval stop);
                    
                    DurationTimer<timeval> static getInstance(string s){
                        return TimeValTimer(s);
                    };
                    
        };


        //todo add description
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

        extern GenericTimer GetDefaultTimingInstance(string label){
            //return GetSystemClockTimingInstance(label);
            return (GenericTimer) GetTimeValTimingInstance(label);
        }
         
        
    }
}
