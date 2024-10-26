#include "Arduino.h"

class StatusLedController
{
private:
    bool currentState = LOW;
    bool isInMenu = false;
    uint8_t pin;

public:
    StatusLedController(uint8_t pin);
    ~StatusLedController();

    void onKeyPressed();
    void onKeyReleased();
    void indicateSelectedKeyMap(uint8_t keyMapNr);
    void onMenuEntered();
    void onMenuLeft();
    void turnOn();
    void turnOff();
};
