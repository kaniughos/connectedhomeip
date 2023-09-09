#include "DurationTimer.h"
#include <stdint.h>
#include <time.h>


#include <string>
using namespace std;
namespace chip{

    namespace timing{

        double TimespecTimer::duration_calc(timespec start, timespec stop){
            return (stop.tv_sec - start.tv_sec)+((stop.tv_nsec - start.tv_nsec) * 1e-9);
        }

    }
}