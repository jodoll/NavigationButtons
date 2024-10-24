#include "Arduino.h"
#include "PhysicalKeyboard.hpp"
#include "Keypad.h"
#include "KeyHandler.hpp"
#include <map>

class KeypadKeyboard : public PhysicalKeyboard
{
private:
    KeyHandler *keyHandler;
    Keypad keypad;
    std::map<char, KeyboardEvent::Key> keymap;

public:
    KeypadKeyboard(KeyHandler &keyHandler, Keypad keypad, std::map<char, KeyboardEvent::Key> keymap)
        : keyHandler(&keyHandler), keypad(keypad), keymap(keymap)
    {
    }
    virtual void scanKeys();
};
