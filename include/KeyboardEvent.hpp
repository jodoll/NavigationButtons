#ifndef KEYBOARD_EVENT
#define KEYBOARD_EVENT

namespace NavigationPad
{
    enum KeyCode
    {
        PLUS = 1,
        MINUS,

        ENTER,
        BACK,

        UP,
        LEFT,
        RIGHT,
        DOWN,
    };

    struct Event
    {
        enum Type
        {
            RELEASED,
            PRESSED,
            HOLD
        };

        KeyCode key;
        Type type;
    };
}

#endif