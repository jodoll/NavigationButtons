#include "keyboard/Keyboard.hpp"
#include "keyboard/NoopKeyMap.hpp"
#include "navigationPad/NavigationPad.hpp"
#include "KeyboardWrapper.hpp"
#include "led/StatusLedController.hpp"
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
    StatusLedController *ledController;
    Keyboard::KeyMap *currentKeyMap = &noopKeyMap;
    KeyboardWrapper wrapper;
    std::map<NavigationPad::KeyCode, std::set<Keyboard::Key>> pressedKeys;
    std::map<Keyboard::Key, FutureKeyPress> repeatingKeys;

    unsigned long lastTick = 0;
    const int repeatingKeyDelayMs = 500;

    void addRepeatingKey(Keyboard::Key &key);
    void removeRepeatingKey(Keyboard::Key &key);
    void releaseKeys(NavigationPad::Event &event);

public:
    KeyHandler(StatusLedController &ledController) : ledController(&ledController) {};
    KeyHandler(StatusLedController &ledController, int repeatingKeyDelayMs)
        : ledController(&ledController), repeatingKeyDelayMs(repeatingKeyDelayMs) {};
    ~KeyHandler(){};

    void connect();
    void setKeyMap(Keyboard::KeyMap &keyMap);
    void handle(NavigationPad::Event event);
    void tick();
};
