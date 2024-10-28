#include "KeyboardWrapper.hpp"

const MediaKeyReport* KeyboardWrapper::toMediaKeyReport(const MediaKeyCode &mediaKey)
{
    switch (mediaKey)
    {
    case MediaKeyCode::NEXT_TRACK:
        return &KEY_MEDIA_NEXT_TRACK;
    case MediaKeyCode::PREVIOUS_TRACK:
        return &KEY_MEDIA_NEXT_TRACK;
    case MediaKeyCode::STOP:
        return &KEY_MEDIA_NEXT_TRACK;
    case MediaKeyCode::PLAY_PAUSE:
        return &KEY_MEDIA_NEXT_TRACK;
    case MediaKeyCode::MUTE:
        return &KEY_MEDIA_NEXT_TRACK;
    case MediaKeyCode::VOLUME_UP:
        return &KEY_MEDIA_NEXT_TRACK;
    case MediaKeyCode::VOLUME_DOWN:
        return &KEY_MEDIA_NEXT_TRACK;
    case MediaKeyCode::WWW_HOME:
        return &KEY_MEDIA_NEXT_TRACK;
    case MediaKeyCode::LOCAL_MACHINE_BROWSER:
        return &KEY_MEDIA_NEXT_TRACK;
    case MediaKeyCode::CALCULATOR:
        return &KEY_MEDIA_NEXT_TRACK;
    case MediaKeyCode::WWW_BOOKMARKS:
        return &KEY_MEDIA_NEXT_TRACK;
    case MediaKeyCode::WWW_SEARCH:
        return &KEY_MEDIA_NEXT_TRACK;
    case MediaKeyCode::WWW_STOP:
        return &KEY_MEDIA_NEXT_TRACK;
    case MediaKeyCode::WWW_BACK:
        return &KEY_MEDIA_NEXT_TRACK;
    case MediaKeyCode::CONSUMER_CONTROL_CONFIGURATION:
        return &KEY_MEDIA_NEXT_TRACK;
    case MediaKeyCode::POWER:
    default:
        return &KEY_MEDIA_NEXT_TRACK;
    }
}

void KeyboardWrapper::connect()
{
    bleKeyboard.begin();
}

void KeyboardWrapper::writeKey(const Keyboard::Key &key)
{
    switch (key.type)
    {
    case Keyboard::Key::Type::SINGLE:
        bleKeyboard.write(key.character);
        if (DEBUG)
            Serial.printf("Sending Key %c\n", key.character);
        break;
    case Keyboard::Key::Type::MEDIA:
        bleKeyboard.write(*toMediaKeyReport(key.mediaKey));
        if (DEBUG)
            Serial.printf("Sending MediaKey %s\n", key.textValue.c_str());
        break;
    }
}

void KeyboardWrapper::holdKey(Keyboard::Key &key)
{
    switch (key.type)
    {
    case Keyboard::Key::Type::SINGLE:
        bleKeyboard.press(key.character);
        if (DEBUG)
            Serial.printf("Writing Key %c\n", key.character);
        break;
    case Keyboard::Key::Type::MEDIA:
        bleKeyboard.press(*toMediaKeyReport(key.mediaKey));
        if (DEBUG)
            Serial.printf("Writing MediaKey %s\n", key.textValue.c_str());
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
        bleKeyboard.release(*toMediaKeyReport(key.mediaKey));
        break;
    }
}

void KeyboardWrapper::releaseAll()
{
    bleKeyboard.releaseAll();
}
