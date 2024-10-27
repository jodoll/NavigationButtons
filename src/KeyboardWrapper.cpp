#include "KeyboardWrapper.hpp"

void KeyboardWrapper::connect(){
    bleKeyboard.begin();
}


void KeyboardWrapper::pressKey(Keyboard::Key &key)
{
    switch (key.type)
    {
    case Keyboard::Key::Type::SINGLE:
        bleKeyboard.press(key.character);
        break;
    case Keyboard::Key::Type::MEDIA:
        bleKeyboard.press(*key.mediaKey);
        break;
    }
}

void KeyboardWrapper::sendKey(const Keyboard::Key &key)
{
    switch (key.type)
    {
    case Keyboard::Key::Type::SINGLE:
        bleKeyboard.write(key.character);
        if (DEBUG)
            Serial.printf("Sending Key %c\n", key.character);
        break;
    case Keyboard::Key::Type::MEDIA:
        bleKeyboard.write(*key.mediaKey);
        if (DEBUG)
            Serial.println("Sending MediaKey");
        break;
    }
}

void KeyboardWrapper::releaseKey(Keyboard::Key &key)
{
    switch (key.type)
    {
    case Keyboard::Key::Type::SINGLE:
        bleKeyboard.release(key.character);
        break;
    case Keyboard::Key::Type::MEDIA:
        bleKeyboard.release(*key.mediaKey);
        break;
    }
}

void KeyboardWrapper::releaseAll()
{
    bleKeyboard.releaseAll();
}
