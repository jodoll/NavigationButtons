#include "keymap/NavigationKeyMap.hpp"
using namespace Keyboard;

std::vector<Keyboard::Press> NavigationKeyMap::lookup(KeyboardEvent::Event event)
{
    Press::Action actionType;
    switch (event.type)
    {
    case KeyboardEvent::Type::RELEASED:
        actionType = Press::Action::RELEASE;
        break;
    case KeyboardEvent::Type::PRESSED:
        actionType = Press::Action::INSTANT;
        break;
    case KeyboardEvent::Type::HOLD:
        actionType = Press::Action::REPEATING;
        break;
    }

    if (event.key == KeyboardEvent::KeyCode::UP)
    {
        return std::vector<Keyboard::Press>({Press(actionType, 'd')});
    }
    return std::vector<Keyboard::Press>();
}