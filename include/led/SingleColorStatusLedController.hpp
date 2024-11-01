#include "Arduino.h"
#include "led/StatusLedController.hpp"

class SingleColorStatusLedController : public StatusLedController
{
private:
    bool currentState = LOW;
    bool isInMenu = false;
    uint8_t pin;

public:
    SingleColorStatusLedController(uint8_t pin);
    ~SingleColorStatusLedController() {};

    void onKeyPressed() override;
    void onKeyReleased() override;
    void indicateSelectedKeyMap(uint8_t keyMapNr) override;
    void onMenuEntered() override {};
    void onMenuLeft() override {};

    void turnOn() override;
    void turnOff() override;
};
