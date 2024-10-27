#include "Arduino.h"
#include "BleKeyboard.h"
#include "navigationPad/NavigationPad.hpp"

#ifndef KEYMAP
#define KEYMAP

namespace Keyboard
{
    struct Key
    {
        enum Type
        {
            SINGLE,
            MEDIA
        };

        Key(uint8_t character) : type(Type::SINGLE), character(character) {}
        Key(const MediaKeyReport *mediaKey) : type(Type::MEDIA), mediaKey(mediaKey) {}

        Type type;
        uint8_t character = 0;
        const MediaKeyReport *mediaKey = nullptr;

        std::string asString();
    };

    struct Press
    {
        enum Action
        {
            INSTANT,
            HOLD,
            REPEATING,
            RELEASE
        };

        Press(Action action, uint8_t character) : action(action), key(character) {}
        Press(Action action, const MediaKeyReport *mediaKey) : action(action), key(mediaKey) {}

        Action action;
        Key key;
    };

    class Map
    {
    private:
    public:
        virtual ~Map() {}
        virtual std::vector<Press> lookup(NavigationPad::Event event) = 0;
    };
}

#endif