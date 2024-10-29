#include "keyboard/NavigationKeyMap.hpp"
#include "BleKeyboard.h"

using namespace Keyboard;

std::vector<Keyboard::Press> NavigationKeyMap::single(NavigationPad::Event::Type action, Key shortPress)
{
    if (action == NavigationPad::Event::Type::PRESSED)
        return std::vector<Keyboard::Press>(
            {Press(Press::Action::INSTANT, shortPress)});
    else
        return std::vector<Keyboard::Press>();
}

std::vector<Keyboard::Press> NavigationKeyMap::repeating(NavigationPad::Event::Type action, Key key)
{
    Press::Action actionType;
    switch (action)
    {
    case NavigationPad::Event::Type::PRESSED:
        actionType = Press::Action::INSTANT;
        break;
    case NavigationPad::Event::Type::HOLD:
        actionType = Press::Action::REPEATING;
        break;
    case NavigationPad::Event::RELEASED:
    default:
        return std::vector<Keyboard::Press>();
    }

    return std::vector<Keyboard::Press>(
        {Press(actionType, key)});
}

std::vector<Keyboard::Press> NavigationKeyMap::hold(NavigationPad::Event::Type action, Key key)
{
    Press::Action actionType;
    switch (action)
    {
    case NavigationPad::Event::Type::HOLD:
        actionType = Press::Action::HOLD;
        break;
    case NavigationPad::Event::RELEASED:
        actionType = Press::Action::INSTANT;
        break;
    default:
    case NavigationPad::Event::Type::PRESSED:
        return std::vector<Keyboard::Press>();
    }

    return std::vector<Keyboard::Press>(
        {Press(actionType, key)});
}

std::vector<Keyboard::Press> NavigationKeyMap::alternative(NavigationPad::Event::Type action, Key shortPress, Key longPress)
{
    Press::Action actionType;
    switch (action)
    {
    case NavigationPad::Event::Type::HOLD:
        return std::vector<Keyboard::Press>(
            {Press(Press::Action::INSTANT, longPress)});
    case NavigationPad::Event::RELEASED:
        return std::vector<Keyboard::Press>(
            {Press(Press::Action::INSTANT, shortPress)});
    case NavigationPad::Event::Type::PRESSED:
    default:
        return std::vector<Keyboard::Press>();
    }
}

std::vector<Keyboard::Press> NavigationKeyMap::lookup(NavigationPad::Event event)
{
    switch (event.key)
    {
    case NavigationPad::KeyCode::PLUS:
        return repeating(event.type, '+');
    case NavigationPad::KeyCode::MINUS:
        return repeating(event.type, '-');
    case NavigationPad::KeyCode::ENTER:
        return alternative(event.type, 'N', 'D');
    case NavigationPad::KeyCode::BACK:
        return single(event.type, 'C');
    case NavigationPad::KeyCode::UP:
        return repeating(event.type, KEY_UP_ARROW);
    case NavigationPad::KeyCode::LEFT:
        return repeating(event.type, KEY_LEFT_ARROW);
    case NavigationPad::KeyCode::RIGHT:
        return repeating(event.type, KEY_RIGHT_ARROW);
    case NavigationPad::KeyCode::DOWN:
        return repeating(event.type, KEY_DOWN_ARROW);
    default:
        return std::vector<Press>();
    };
}