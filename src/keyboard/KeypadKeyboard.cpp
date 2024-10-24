#include "keyboard/KeypadKeyboard.hpp"

void KeypadKeyboard::scanKeys()
{
    // map key code
    // Could use getKeys() if we did support multiple key presses
    char keyCode = keypad.getKey();
    if (keyCode == NO_KEY)
        return;

    auto iterator = keymap.find(keyCode);
    if (iterator == keymap.end())
        return; // char not found in map (== configuration error)
    KeyboardEvent::Key key = iterator->second;

    // map event type
    KeyState state = keypad.getState(); 
    KeyboardEvent::Type type;
    switch (state)
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

    keyHandler->handle(KeyboardEvent::Event{key, type});
}
