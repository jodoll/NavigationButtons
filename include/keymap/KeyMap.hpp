#include "Arduino.h"
#include "BleKeyboard.h"
#include "KeyboardEvent.hpp"

#ifndef KEYMAP
#define KEYMAP

namespace Keyboard
{
    struct KeyPress
    {
        enum ActionType
        {
            INSTANT,
            HOLD,
            REPEATING,
            RELEASE
        };
        enum KeyType
        {
            SINGLE,
            MEDIA
        };
        struct Key
        {
            Key(uint8_t character) : type(KeyType::SINGLE), character(character) {}
            Key(const MediaKeyReport *mediaKey) : type(KeyType::MEDIA), mediaKey(mediaKey) {}

            KeyType type;
            uint8_t character = 0;
            const MediaKeyReport *mediaKey = nullptr;

            std::string asString()
            {
                switch (type)
                {
                case Keyboard::KeyPress::KeyType::SINGLE:
                    return std::string(1, character);
                case Keyboard::KeyPress::KeyType::MEDIA:
                    return std::to_string(reinterpret_cast<uintptr_t>(mediaKey));
                    break;
                }
                return std::string();
            }
        };

        KeyPress(ActionType action, uint8_t character) : action(action), key(character) {}
        KeyPress(ActionType action, const MediaKeyReport *mediaKey) : action(action), key(mediaKey) {}

        ActionType action;
        Key key;
    };

    class KeyMap
    {
    private:
    public:
        virtual ~KeyMap() {}
        virtual std::vector<KeyPress> lookup(KeyboardEvent::Event event) = 0;
    };
}

#endif