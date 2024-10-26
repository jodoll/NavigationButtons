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
            RELEASE
        };
        enum KeyType
        {
            SINGLE,
            MEDIA
        };

        KeyPress(ActionType action, uint8_t character) : action(action), type(KeyType::SINGLE), character(character){}
        KeyPress(ActionType action, const MediaKeyReport* mediaKey) : action(action), type(KeyType::MEDIA), mediaKey(mediaKey){}

        ActionType action;
        KeyType type;
        uint8_t character = 0;
        const MediaKeyReport* mediaKey = nullptr;
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