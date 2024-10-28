#include "keyboard/Keyboard.hpp"
#include "BleKeyboard.h"

class KeyboardWrapper
{
private:
    BleKeyboard bleKeyboard = BleKeyboard("NavigationButtons", "jodoll", 100);
    const MediaKeyReport* toMediaKeyReport(const MediaKeyCode &mediaKey);

public:
    void connect();
    void writeKey(const Keyboard::Key &key);
    void holdKey(Keyboard::Key &key);
    void releaseKey(Keyboard::Key &key);
    void releaseAll();
};
