#include "keymap/KeyMap.hpp"
#include "keymap/NoopKeyMap.hpp"
#include "KeyboardEvent.hpp"
#include "KeyboardWrapper.hpp"
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
    KeyboardWrapper wrapper;
    std::map<std::string, FutureKeyPress> repeatingKeys;

    unsigned long lastTick = 0;
    const int repeatingKeyDelayMs = 500;

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
