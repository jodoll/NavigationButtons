#include "keymap/KeyMap.hpp"
#include "BleKeyboard.h"

class KeyboardWrapper
{
private:
    BleKeyboard bleKeyboard = BleKeyboard("NavigationButtons", "jodoll", 100);

public:
    void connect();
    void pressKey(Keyboard::KeyPress::Key &key);
    void sendKey(const Keyboard::KeyPress::Key &key);
    void releaseKey(Keyboard::KeyPress::Key &key);
    void releaseAll();
};
