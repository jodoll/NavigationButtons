#include "keyboard/NavigationKeyMap.hpp"
#include "keyboard/KeyCodes.hpp"

using namespace Keyboard;
using NavigationPad::Event;
using Keyboard::Press;

std::vector<Press> NavigationKeyMap::single(Event::Type action, Key shortPress)
{
    if (action == Event::PRESSED)
        return std::vector<Press>(
            {Press(Press::INSTANT, shortPress)});
    else
        return std::vector<Press>();
}

std::vector<Press> NavigationKeyMap::repeating(Event::Type action, Key key)
{
    Press::Action actionType;
    switch (action)
    {
    case Event::PRESSED:
        actionType = Press::INSTANT;
        break;
    case Event::HOLD:
        actionType = Press::REPEATING;
        break;
    case Event::RELEASED:
    case Event::RELEASED_HOLD:
        return std::vector<Press>(
            {Press(Press::RELEASE, key)});
    }

    return std::vector<Press>(
        {Press(actionType, key)});
}

std::vector<Press> NavigationKeyMap::hold(Event::Type action, Key key)
{
    Press::Action actionType;
    switch (action)
    {
    case Event::PRESSED:
        return std::vector<Press>();
    case Event::HOLD:
        actionType = Press::HOLD;
        break;
    case Event::RELEASED_HOLD:
        actionType = Press::RELEASE;
        break;
    case Event::RELEASED:
        actionType = Press::INSTANT;
        break;
    }

    return std::vector<Press>(
        {Press(actionType, key)});
}

std::vector<Press> NavigationKeyMap::alternative(Event::Type action, Key shortPress, Key longPress)
{
    switch (action)
    {
    case Event::HOLD:
        return std::vector<Press>(
            {Press(Press::INSTANT, longPress)});
    case Event::RELEASED:
        return std::vector<Press>(
            {Press(Press::INSTANT, shortPress)});
    case Event::PRESSED:
    case Event::RELEASED_HOLD:
        return std::vector<Press>();
    }

}
std::vector<Press> NavigationKeyMap::alternativeRepeating(Event::Type action, Key shortPress, Key longPress)
{
    switch (action)
    {
    case Event::HOLD:
        return std::vector<Press>(
            {Press(Press::REPEATING, longPress)});
    case Event::RELEASED_HOLD:
        return std::vector<Press>{
            {Press(Press::RELEASE, longPress)}
        };
    case Event::RELEASED:
        return std::vector<Press>(
            {Press(Press::INSTANT, shortPress)});
    case Event::PRESSED:
        return std::vector<Press>();
    }
}

std::vector<Press> NavigationKeyMap::lookup(Event event)
{
    switch (event.key)
    {
    case NavigationPad::PLUS:
        return repeating(event.type, '+');
    case NavigationPad::MINUS:
        return repeating(event.type, '-');
    case NavigationPad::ENTER:
        return alternative(event.type, 'N', 'D');
    case NavigationPad::BACK:
        return single(event.type, 'C');
    case NavigationPad::UP:
        return repeating(event.type, KEY_UP_ARROW);
    case NavigationPad::LEFT:
        return repeating(event.type, KEY_LEFT_ARROW);
    case NavigationPad::RIGHT:
        return repeating(event.type, KEY_RIGHT_ARROW);
    case NavigationPad::DOWN:
        return repeating(event.type, KEY_DOWN_ARROW);
    default:
        return std::vector<Press>();
    };
}