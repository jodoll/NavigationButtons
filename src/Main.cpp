#include "Arduino.h"
#include "Flags.hpp"
#include "navigationPad/BarButtons.hpp"
#include "BleKeyboard.h"
#include "keyboard/NavigationKeyMap.hpp"
#include "bleKeyboard/BleKeyboardWrapper.hpp"
#include "led/SingleColorStatusLedController.hpp"

BleKeyboardWrapper keyboardWrapper = BleKeyboardWrapper();
SingleColorStatusLedController ledController = SingleColorStatusLedController(BarButtons::ledPin);
KeyHandler keyHandler = KeyHandler(ledController, keyboardWrapper);
KeypadNavigationPad keypadKeyboard = BarButtons::keypad(keyHandler);
PhysicalNavigationPad& keyboard = keypadKeyboard;

NavigationKeyMap navigationKeyMap;

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
    keyHandler.setKeyMap(navigationKeyMap);


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
    keyHandler.tick();
}