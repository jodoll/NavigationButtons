#include "Arduino.h"
#include "keyboard/KeypadKeyboard.hpp"

KeypadKeyboard barButtons(KeyHandler &handler){
    // Keypad library settings
    static const byte ROWS = 3;
    static const byte COLS = 3;
    char keys[ROWS][COLS] = {
        {'1', '5', '4'},
        {'2', '6', '7'},
        {'3', '8', '9'}};
    
    std::map<char, KeyboardEvent::Key> keymap = {
        {'1', KeyboardEvent::PLUS},
        {'2', KeyboardEvent::MINUS},
        {'3', KeyboardEvent::ENTER},
        {'4', KeyboardEvent::BACK},
        {'5', KeyboardEvent::UP},
        {'6', KeyboardEvent::LEFT},
        {'7', KeyboardEvent::RIGHT},
        {'8', KeyboardEvent::DOWN},
    };

    // Assignment of pins (depending on how they are wried)
    static const int LED_PIN = 6;   // Status led
    byte rowPins[COLS] = {2, 1, 0}; // Keypad pins, top to bottom
    byte colPins[ROWS] = {3, 4, 5}; // Keypad pins, left to right

    Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
    return KeypadKeyboard(handler, keypad, keymap);
}
