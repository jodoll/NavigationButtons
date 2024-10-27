#include "Arduino.h"
#include "navigationPad/PhysicalNavigationPad.hpp"
#include "Keypad.h"
#include "KeyHandler.hpp"
#include <map>

class KeypadNavigationPad : public PhysicalNavigationPad
{
private:
    KeyHandler *keyHandler;
    Keypad keypad;
    std::map<char, NavigationPad::KeyCode> keymap;

    void handleKey(Key &key);
public:
    KeypadNavigationPad(KeyHandler &keyHandler, Keypad keypad, std::map<char, NavigationPad::KeyCode> keymap)
        : keyHandler(&keyHandler), keypad(keypad), keymap(keymap)
    {
    }
    virtual void scanKeys();
};
