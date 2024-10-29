#include "keyboard/NavigationKeyMap.hpp"
using namespace Keyboard;

std::vector<Keyboard::Press> NavigationKeyMap::lookup(NavigationPad::Event event)
{
    Press::Action actionType;
    switch (event.type)
    {
    case NavigationPad::Event::Type::PRESSED:
        actionType = Press::Action::INSTANT;
        break;
    case NavigationPad::Event::Type::HOLD:
        actionType = Press::Action::REPEATING;
        break;
    case NavigationPad::Event::RELEASED:
        return std::vector<Keyboard::Press>();
    }

    if (event.key == NavigationPad::KeyCode::UP)
    {
        return std::vector<Keyboard::Press>({Press(actionType, 'd')});
    }
    else if (event.key == NavigationPad::KeyCode::RIGHT)
    {
        return std::vector<Keyboard::Press>({Press(actionType, MediaKeyCode::CALCULATOR)});
    }
    return std::vector<Keyboard::Press>();
}