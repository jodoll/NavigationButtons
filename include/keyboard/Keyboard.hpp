#include "Arduino.h"
#include "navigationPad/NavigationPad.hpp"
#include "keyboard/MediaKey.hpp"
#include <vector>

#ifndef KEYBOARD
#define KEYBOARD

namespace Keyboard
{
    struct Key
    {
        enum Type
        {
            SINGLE,
            MEDIA
        };

        Key(uint8_t character)
            : type(Type::SINGLE),
              character(character),
              textValue(std::string(1, character)) {}
        Key(const MediaKeyCode mediaKey)
            : type(Type::MEDIA),
              mediaKey(mediaKey),
              textValue(mediaKeyReportToText(mediaKey)) {}

        Type type;
        uint8_t character = 0;
        const MediaKeyCode mediaKey = MediaKeyCode::POWER;
        const std::string textValue;

        bool operator<(const Key &other) const
        {
            return textValue < other.textValue;
        }
    };

    struct Press
    {
        enum Action
        {
            INSTANT,
            HOLD,
            REPEATING
            // RELEASE
        };

        Press(Action action, uint8_t character) : action(action), key(character) {}
        Press(Action action, const MediaKeyCode mediaKey) : action(action), key(mediaKey) {}

        Action action;
        Key key;
    };

    class KeyMap
    {
    private:
    public:
        virtual ~KeyMap() {}
        virtual std::vector<Press> lookup(NavigationPad::Event event) = 0;
    };
}

#endif