#include "KeyboardWrapper.hpp"

void KeyboardWrapper::connect(){
    bleKeyboard.begin();
}


void KeyboardWrapper::pressKey(Keyboard::KeyPress::Key &key)
{
    switch (key.type)
    {
    case Keyboard::KeyPress::KeyType::SINGLE:
        bleKeyboard.press(key.character);
        break;
    case Keyboard::KeyPress::KeyType::MEDIA:
        bleKeyboard.press(*key.mediaKey);
        break;
    }
}

void KeyboardWrapper::sendKey(const Keyboard::KeyPress::Key &key)
{
    switch (key.type)
    {
    case Keyboard::KeyPress::KeyType::SINGLE:
        bleKeyboard.write(key.character);
        if (DEBUG)
            Serial.printf("Sending Key %c\n", key.character);
        break;
    case Keyboard::KeyPress::KeyType::MEDIA:
        bleKeyboard.write(*key.mediaKey);
        if (DEBUG)
            Serial.println("Sending MediaKey");
        break;
    }
}

void KeyboardWrapper::releaseKey(Keyboard::KeyPress::Key &key)
{
    switch (key.type)
    {
    case Keyboard::KeyPress::KeyType::SINGLE:
        bleKeyboard.release(key.character);
        break;
    case Keyboard::KeyPress::KeyType::MEDIA:
        bleKeyboard.release(*key.mediaKey);
        break;
    }
}

void KeyboardWrapper::releaseAll()
{
}
