#include "SystemClock.hpp"
#ifdef ARDUINO
#include "Arduino.h"
#else
#include <chrono>
using namespace std::chrono;
#endif

SystemClock systemClock = SystemClock(); 

unsigned long SystemClock::currentTimeMillis()
{
#ifdef ARDUINO
    return millis();
#else
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
#endif
}