#ifndef KEYBOARD_EVENT
#define KEYBOARD_EVENT

namespace KeyboardEvent
{
    enum KeyCode
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,

        ENTER,
        BACK,

        PLUS,
        MINUS
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