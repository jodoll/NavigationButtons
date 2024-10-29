#include "KeyboardWrapper.hpp"

const MediaKeyReport *KeyboardWrapper::toMediaKeyReport(const MediaKeyCode &mediaKey)
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

// MediaReportKey
std::string KeyboardWrapper::MediaReportKey::asText()
{
    return text;
}
void KeyboardWrapper::MediaReportKey::writeKey(BleKeyboard &keyboard)
{
    keyboard.write(*report);
}
void KeyboardWrapper::MediaReportKey::holdKey(BleKeyboard &keyboard)
{
    keyboard.press(*report);
}
void KeyboardWrapper::MediaReportKey::releaseKey(BleKeyboard &keyboard)
{
    keyboard.release(*report);
}

// CharKey
std::string KeyboardWrapper::CharKey::asText()
{
    return text;
}
void KeyboardWrapper::CharKey::writeKey(BleKeyboard &keyboard)
{
    keyboard.write(character);
}
void KeyboardWrapper::CharKey::holdKey(BleKeyboard &keyboard)
{
    keyboard.press(character);
}
void KeyboardWrapper::CharKey::releaseKey(BleKeyboard &keyboard)
{
    keyboard.release(character);
}

// KeboardWrapper
std::shared_ptr<KeyboardWrapper::BleKey> KeyboardWrapper::toBleKey(const Keyboard::Key &key)
{
    switch (key.type)
    {
    case Keyboard::Key::Type::MEDIA:
        return std::static_pointer_cast<KeyboardWrapper::BleKey>(
            std::make_shared<KeyboardWrapper::MediaReportKey>(key.mediaKey, key.textValue));
    case Keyboard::Key::Type::SINGLE:
    default:
        return std::static_pointer_cast<KeyboardWrapper::BleKey>(
            std::make_shared<KeyboardWrapper::CharKey>(key.character));
    }
}

void KeyboardWrapper::connect()
{
    bleKeyboard.begin();
}

void KeyboardWrapper::writeKey(const Keyboard::Key &key)
{
    auto bleKey = toBleKey(key);
    bleKey->writeKey(bleKeyboard);
    if (DEBUG)
        Serial.printf("Writing Key %s\n", bleKey->asText().c_str());
}

void KeyboardWrapper::holdKey(Keyboard::Key &key)
{
    auto bleKey = toBleKey(key);
    bleKey->holdKey(bleKeyboard);
    if (DEBUG)
        Serial.printf("Holding Key %s down\n", bleKey->asText().c_str());
}

void KeyboardWrapper::releaseKey(Keyboard::Key &key)
{
    auto bleKey = toBleKey(key);
    bleKey->releaseKey(bleKeyboard);
    if (DEBUG)
        Serial.printf("Releasing Key %s\n", bleKey->asText().c_str());
}

void KeyboardWrapper::releaseAll()
{
    bleKeyboard.releaseAll();
    if (DEBUG)
        Serial.println("Releasing all keys");
}
