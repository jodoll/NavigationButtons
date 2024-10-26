#include "keymap/NoopKeyMap.hpp"

std::vector<Keyboard::KeyPress> NoopKeyMap::lookup(KeyboardEvent::Event event)
{
    return std::vector<Keyboard::KeyPress>();
}