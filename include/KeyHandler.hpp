#include "keymap/KeyMap.hpp"
#include "keymap/NoopKeyMap.hpp"
#include "KeyboardEvent.hpp"
#include "BleKeyboard.h"
#include "led/StatusLedController.hpp"

class KeyHandler
{
private:
    static NoopKeyMap noopKeyMap;
    StatusLedController *ledController;
    Keyboard::KeyMap *currentKeyMap = &noopKeyMap;
    BleKeyboard bleKeyboard = BleKeyboard("NavigationButtons", "jodoll", 100);

    void releaseKeys(Keyboard::KeyPress &keyPress);
    void pressKeys(Keyboard::KeyPress &keyPress);
    void sendKeys(Keyboard::KeyPress &keyPress);
public:
    KeyHandler(StatusLedController &ledController) : ledController(&ledController){};
    ~KeyHandler();

    void connect();
    void setKeyMap(Keyboard::KeyMap &keyMap);
    void handle(KeyboardEvent::Event event);
};
