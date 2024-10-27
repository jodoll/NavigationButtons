#include "keypad/KeypadKeyboard.hpp"

void KeypadKeyboard::scanKeys()
{
    if (!keypad.getKeys())
        return;

    for (Key key : keypad.key)
    {
        handleKey(key);
    }
}

void KeypadKeyboard::handleKey(Key &key)
{
    if (!key.stateChanged)
        return;

    auto iterator = keymap.find(key.kchar);
    if (iterator == keymap.end())
        return; // char not found in map (== configuration error)
    KeyboardEvent::KeyCode keyCode = iterator->second;

    // map event type
    KeyboardEvent::Type type;
    switch (key.kstate)
    {
    case PRESSED:
        type = KeyboardEvent::Type::PRESSED;
        break;
    case HOLD:
        type = KeyboardEvent::Type::HOLD;
        break;
    case RELEASED:
        type = KeyboardEvent::Type::RELEASED;
        break;
    case IDLE:
        return;
    };

    keyHandler->handle(KeyboardEvent::Event{keyCode, type});
}
