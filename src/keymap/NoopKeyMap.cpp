#include "keymap/NoopKeyMap.hpp"

std::vector<Keyboard::Press> NoopKeyMap::lookup(KeyboardEvent::Event event)
{
    return std::vector<Keyboard::Press>();
}