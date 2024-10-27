#include "keyboard/NoopKeyMap.hpp"

std::vector<Keyboard::Press> NoopKeyMap::lookup(NavigationPad::Event event)
{
    return std::vector<Keyboard::Press>();
}