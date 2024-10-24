#include "KeyMap.hpp"
#include "KeyboardEvent.hpp"

class KeyHandler
{
private:
    KeyMap *currentKeyMap = nullptr;

public:
    static KeyHandler &noop()
    {
        static KeyHandler instance;
        return instance;
    }

    KeyHandler() {};
    ~KeyHandler();

    void setKeyMap(KeyMap &keyMap);
    void handle(KeyboardEvent::Event event);
};
