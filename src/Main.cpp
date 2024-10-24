#include "Arduino.h"
#include "keyboard/BarButtons.hpp"
#include "BleKeyboard.h"

#ifndef DEBUG
#define DEBUG 0
#endif

KeyHandler keyHandler = KeyHandler();
KeypadKeyboard keypadKeyboard = barButtons(keyHandler);
PhysicalKeyboard& keyboard = keypadKeyboard;
BleKeyboard bleKeyboard = BleKeyboard("EspKeyboard", "jodoll", 100);


void setup()
{
    if (DEBUG)
    {
        // Might block until serial is actually connected in debug mode
        Serial.begin(9600);
    }

    bleKeyboard.begin();

    // // Handle all keypad events through this listener
    //keypad.addEventListener(keypad_handler); // Add an event listener for this keypad

    // // set HoldTime
    // keypad.setHoldTime(long_press_time);

    // // Enable the led to indicate we're switched on
    // pinMode(LED_PIN, OUTPUT);

    // // End of setup()
    // if (DEBUG)
    // {
    //     Serial.println("Good to go!");
    // }
}
void loop()
{
    keyboard.scanKeys();
}