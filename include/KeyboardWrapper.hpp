#include "keymap/Keyboard.hpp"
#include "BleKeyboard.h"

class KeyboardWrapper
{
private:
    BleKeyboard bleKeyboard = BleKeyboard("NavigationButtons", "jodoll", 100);

public:
    void connect();
    void pressKey(Keyboard::Key &key);
    void sendKey(const Keyboard::Key &key);
    void releaseKey(Keyboard::Key &key);
    void releaseAll();
};
