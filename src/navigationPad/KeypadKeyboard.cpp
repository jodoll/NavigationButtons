#include "navigationPad/KeypadKeyboard.hpp"

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
    NavigationPad::KeyCode keyCode = iterator->second;

    // map event type
    NavigationPad::Event::Type type;
    switch (key.kstate)
    {
    case PRESSED:
        type = NavigationPad::Event::Type::PRESSED;
        break;
    case HOLD:
        type = NavigationPad::Event::Type::HOLD;
        break;
    case RELEASED:
        type = NavigationPad::Event::Type::RELEASED;
        break;
    case IDLE:
        return;
    };

    keyHandler->handle(NavigationPad::Event{keyCode, type});
}
