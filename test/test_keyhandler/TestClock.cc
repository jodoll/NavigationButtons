#include "clock/Clock.hpp"

class TestClock : public Clock {
public:
    unsigned long time = 0;

    void advanceBy(unsigned long millis){
        time += millis;
    }

    unsigned long currentTimeMillis() override{
        return time;
    }
};