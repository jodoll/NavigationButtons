#include "keymap/NavigationKeyMap.hpp"
using namespace Keyboard;

std::vector<Keyboard::KeyPress> NavigationKeyMap::lookup(KeyboardEvent::Event event)
{
    KeyPress::ActionType actionType;
    switch (event.type)
    {
    case KeyboardEvent::Type::RELEASED:
        actionType = KeyPress::ActionType::RELEASE;
        break;
    case KeyboardEvent::Type::PRESSED:
        actionType = KeyPress::ActionType::INSTANT;
        break;
    case KeyboardEvent::Type::HOLD:
        actionType = KeyPress::ActionType::REPEATING;
        break;
    }

    if (event.key == KeyboardEvent::KeyCode::UP)
    {
        return std::vector<Keyboard::KeyPress>({KeyPress(actionType, 'd')});
    }
    return std::vector<Keyboard::KeyPress>();
}