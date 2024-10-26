#include "led/StatusLedController.hpp"

const int keyMapSelectedPulseDurationMs = 300;

StatusLedController::StatusLedController(uint8_t pin)
{
    this->pin = pin;
    pinMode(pin, OUTPUT);
}

void StatusLedController::turnOn()
{
    currentState = HIGH;
    digitalWrite(pin, HIGH);
}

void StatusLedController::turnOff()
{
    currentState = LOW;
    digitalWrite(pin, LOW);
}

void StatusLedController::onKeyPressed()
{
    if (isInMenu)
        return;
    turnOn();
}

void StatusLedController::onKeyReleased()
{
    if (isInMenu)
        return;
    turnOff();
}

void StatusLedController::indicateSelectedKeyMap(uint8_t keyMapNr)
{
    boolean previousState = currentState;
    if (currentState == HIGH)
    {
        turnOff();
        delay(keyMapSelectedPulseDurationMs);
    }

    for (uint8_t i = 0; i < keyMapNr; i++)
    {
        digitalWrite(pin, HIGH);
        delay(keyMapSelectedPulseDurationMs);
        digitalWrite(pin, LOW);
        if (i < keyMapNr - 1)
        {
            delay(keyMapSelectedPulseDurationMs);
        }
    }

    if (previousState == HIGH)
    {
        delay(keyMapSelectedPulseDurationMs);
        turnOn();
    }
};