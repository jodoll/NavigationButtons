#ifndef KEYBOARD_EVENT
#define KEYBOARD_EVENT

namespace KeyboardEvent
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

    enum Type
    {
        PRESSED,
        HOLD,
        RELEASED
    };

    struct Event
    {
        KeyCode key;
        Type type;
    };
}

#endif