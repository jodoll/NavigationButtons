#include "keyboard/Keyboard.hpp"

std::string Keyboard::Key::asString()
{
    switch (type)
    {
    case Keyboard::Key::Type::SINGLE:
        return std::string(1, character);
    case Keyboard::Key::Type::MEDIA:
        return std::to_string(reinterpret_cast<uintptr_t>(mediaKey));
        break;
    }
    return std::string();
}