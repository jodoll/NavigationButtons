#include "Arduino.h"
#include "navigationPad/KeypadKeyboard.hpp"

namespace BarButtons
{
    const uint8_t ledPin = 6;
    KeypadKeyboard keypad(KeyHandler &handler)
    {
        // Keypad library settings
        static const byte ROWS = 3;
        static const byte COLS = 3;
        char keys[ROWS][COLS] = {
            {'1', '5', '4'},
            {'2', '6', '7'},
            {'3', '8', '9'}};

        std::map<char, NavigationPad::KeyCode> keymap = {
            {'1', NavigationPad::PLUS},
            {'2', NavigationPad::MINUS},
            {'3', NavigationPad::ENTER},
            {'4', NavigationPad::BACK},
            {'5', NavigationPad::UP},
            {'6', NavigationPad::LEFT},
            {'7', NavigationPad::RIGHT},
            {'8', NavigationPad::DOWN},
        };

        // Assignment of pins (depending on how they are wried)
        static const int LED_PIN = 6;   // Status led
        byte rowPins[COLS] = {2, 1, 0}; // Keypad pins, top to bottom
        byte colPins[ROWS] = {3, 4, 5}; // Keypad pins, left to right

        Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
        return KeypadKeyboard(handler, keypad, keymap);
    }
}