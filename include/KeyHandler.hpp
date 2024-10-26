#include "keymap/KeyMap.hpp"
#include "keymap/NoopKeyMap.hpp"
#include "KeyboardEvent.hpp"
#include "BleKeyboard.h"

class KeyHandler
{
private:
    static NoopKeyMap noopKeyMap;
    Keyboard::KeyMap *currentKeyMap = &noopKeyMap;
    BleKeyboard bleKeyboard = BleKeyboard("NavigationButtons", "jodoll", 100);

    void releaseKeys(Keyboard::KeyPress &keyPress);
    void pressKeys(Keyboard::KeyPress &keyPress);
    void sendKeys(Keyboard::KeyPress &keyPress);
public:
    KeyHandler() {};
    ~KeyHandler();

    void connect();
    void setKeyMap(Keyboard::KeyMap &keyMap);
    void handle(KeyboardEvent::Event event);
};
