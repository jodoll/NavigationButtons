#include <cstdint>

#ifndef STATUS_LED_CONTROLLER
#define STATUS_LED_CONTROLLER

class StatusLedController
{
public:
    virtual ~StatusLedController() {}
    virtual void onKeyPressed() = 0;
    virtual void onKeyReleased() = 0;
    virtual void indicateSelectedKeyMap(uint8_t keyMapNr) = 0;
    virtual void onMenuEntered() = 0;
    virtual void onMenuLeft() = 0;
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
};

#endif