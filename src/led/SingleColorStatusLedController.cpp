#include "led/SingleColorStatusLedController.hpp"
#include "Arduino.h"

const int keyMapSelectedPulseDurationMs = 300;

SingleColorStatusLedController::SingleColorStatusLedController(uint8_t pin)
{
    this->pin = pin;
    pinMode(pin, OUTPUT);
}

void SingleColorStatusLedController::turnOn()
{
    currentState = HIGH;
    digitalWrite(pin, HIGH);
}

void SingleColorStatusLedController::turnOff()
{
    currentState = LOW;
    digitalWrite(pin, LOW);
}

void SingleColorStatusLedController::onKeyPressed()
{
    if (isInMenu)
        return;
    turnOn();
}

void SingleColorStatusLedController::onKeyReleased()
{
    if (isInMenu)
        return;
    turnOff();
}

void SingleColorStatusLedController::indicateSelectedKeyMap(uint8_t keyMapNr)
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