#include "Arduino.h"
#include "Flags.hpp"
#include "keyboard/BarButtons.hpp"
#include "BleKeyboard.h"

StatusLedController ledController = StatusLedController(BarButtons::ledPin);
KeyHandler keyHandler = KeyHandler(ledController);
KeypadKeyboard keypadKeyboard = BarButtons::keypad(keyHandler);
PhysicalKeyboard& keyboard = keypadKeyboard;

void setup()
{
    if (DEBUG)
    {
        // Might block until serial is actually connected in debug mode
        // Depends on the board, known boards to block:
        // Liolin C3
        Serial.begin(9600);
        Serial.println("Serial Connected");
    }
    keyHandler.connect();


    // // Handle all keypad events through this listener
    //keypad.addEventListener(keypad_handler); // Add an event listener for this keypad

    // // set HoldTime
    // keypad.setHoldTime(long_press_time);

    // // Enable the led to indicate we're switched on

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