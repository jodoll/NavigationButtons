#include "led/StatusLedController.hpp"

#ifndef NOOP_STATUS_LED_CONTROLLER
#define NOOP_STATUS_LED_CONTROLLER

class NoopStatusLedController : public StatusLedController
{
public:
    void onKeyPressed() override {}
    void onKeyReleased() override {}
    void indicateSelectedKeyMap(uint8_t keyMapNr) override {}
    void onMenuEntered() override {}
    void onMenuLeft() override {}
    void turnOn() override {}
    void turnOff() override {}
};

#endif