#include "keymap/KeyMap.hpp"
#include "keymap/NoopKeyMap.hpp"
#include "KeyboardEvent.hpp"
#include "BleKeyboard.h"
#include "led/StatusLedController.hpp"

class KeyHandler
{
private:
    struct FutureKeyPress
    {
        Keyboard::KeyPress::Key key;
        unsigned long pressAfter;
    };
    
    static NoopKeyMap noopKeyMap;
    StatusLedController *ledController;
    Keyboard::KeyMap *currentKeyMap = &noopKeyMap;
    BleKeyboard bleKeyboard = BleKeyboard("NavigationButtons", "jodoll", 100);
    std::map<std::string, FutureKeyPress> repeatingKeys;
    int repeatingKeyDelayMs = 500;

    std::string asString(Keyboard::KeyPress::Key &key);
    void releaseKey(Keyboard::KeyPress::Key &key);
    void pressKey(Keyboard::KeyPress::Key &key);
    void sendKeys(const Keyboard::KeyPress::Key &key);
    void addRepeatingKey(Keyboard::KeyPress::Key &key);
    void removeRepeatingKey(Keyboard::KeyPress::Key &key);

public:
    KeyHandler(StatusLedController &ledController) : ledController(&ledController) {};
    KeyHandler(StatusLedController &ledController, int repeatingKeyDelayMs)
        : ledController(&ledController), repeatingKeyDelayMs(repeatingKeyDelayMs) {};
    ~KeyHandler();

    void connect();
    void setKeyMap(Keyboard::KeyMap &keyMap);
    void handle(KeyboardEvent::Event event);
    void tick();
};
