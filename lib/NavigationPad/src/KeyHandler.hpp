#include "keyboard/Keyboard.hpp"
#include "keyboard/NoopKeyMap.hpp"
#include "navigationPad/NavigationPad.hpp"
#include "KeyboardWrapper.hpp"
#include "led/StatusLedController.hpp"
#include "clock/SystemClock.hpp"
#include <set>

class KeyHandler
{
private:
    struct FutureKeyPress
    {
        Keyboard::Key key;
        unsigned long pressAfter;
    };

    static NoopKeyMap noopKeyMap;
    Keyboard::KeyMap *currentKeyMap = &noopKeyMap;
    StatusLedController *ledController;
    KeyboardWrapper *wrapper;
    Clock *clock = &systemClock;
    std::set<Keyboard::Key> pressedKeys;
    std::map<Keyboard::Key, FutureKeyPress> repeatingKeys;

    bool repeatingKeysChanged = false;
    unsigned long lastTick = 0;

    void addRepeatingKey(Keyboard::Key &key);
    void releaseKeyIfPressed(Keyboard::Key &key);
    void removeKeyIfRepeating(Keyboard::Key &key);

public:
    std::set<NavigationPad::KeyCode> consumedKeyCodes;
    KeyHandler(StatusLedController &ledController, KeyboardWrapper &wrapper)
        : ledController(&ledController), wrapper(&wrapper) {};
    KeyHandler(StatusLedController &ledController, KeyboardWrapper &wrapper, int repeatingKeyDelayMs)
        : ledController(&ledController), wrapper(&wrapper), repeatingKeyDelayMs(repeatingKeyDelayMs) {};
    ~KeyHandler() {};

    const int repeatingKeyDelayMs = 500;
    void setClock(Clock &clock);

    void connect();
    void setKeyMap(Keyboard::KeyMap &keyMap);
    void handle(NavigationPad::Event event);
    void tick();
};
