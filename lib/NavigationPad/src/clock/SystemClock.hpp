#include "clock/Clock.hpp"

class SystemClock: public Clock
{
public:
    unsigned long currentTimeMillis() override;
};

extern SystemClock systemClock;