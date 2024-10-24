namespace KeyboardEvent
{
    enum Key
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
        Key key;
        Type type;
    };
}
