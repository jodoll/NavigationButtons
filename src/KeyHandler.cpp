#include "KeyHandler.hpp"
#include "Flags.hpp"

NoopKeyMap KeyHandler::noopKeyMap = NoopKeyMap();

void KeyHandler::connect()
{
    bleKeyboard.begin();
    ledController->indicateSelectedKeyMap(3);
}

void KeyHandler::setKeyMap(Keyboard::KeyMap &keyMap)
{
    bleKeyboard.releaseAll();
    currentKeyMap = &keyMap;
}

void KeyHandler::handle(KeyboardEvent::Event event)
{
    if (DEBUG)
        Serial.printf("Event: Type=%d, Key=%d\n", event.type, event.key);

    if (event.type < KeyboardEvent::Type::RELEASED)
        ledController->onKeyPressed();
    auto keyPresses = currentKeyMap->lookup(event);
    for (Keyboard::KeyPress keyPress : keyPresses)
    {
        switch (keyPress.action)
        {
        case Keyboard::KeyPress::ActionType::INSTANT:
            sendKeys(keyPress.key);
            break;
        case Keyboard::KeyPress::ActionType::HOLD:
            pressKey(keyPress.key);
            break;
        case Keyboard::KeyPress::ActionType::REPEATING:
            addRepeatingKey(keyPress.key);
            break;
        case Keyboard::KeyPress::ActionType::RELEASE:
            releaseKey(keyPress.key);
            break;
        }
    }
    if (event.type == KeyboardEvent::Type::RELEASED)
        ledController->onKeyReleased();
}

void KeyHandler::releaseKey(Keyboard::KeyPress::Key &key)
{
    removeRepeatingKey(key);
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

void KeyHandler::pressKey(Keyboard::KeyPress::Key &key)
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

void KeyHandler::sendKeys(const Keyboard::KeyPress::Key &key)
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

unsigned long lastTick = 0;
void KeyHandler::tick()
{
    auto now = millis();
    if (now < lastTick + 20)
        return;

    for (auto &entry : repeatingKeys)
    {
        auto &futurePress = entry.second;
        if (now >= futurePress.pressAfter)
        {
            auto remainingTimeToNextPress = repeatingKeyDelayMs - ((now - futurePress.pressAfter) % repeatingKeyDelayMs);
            futurePress.pressAfter += remainingTimeToNextPress;
            sendKeys(futurePress.key);
        }
    };
    lastTick = now;
}

void KeyHandler::addRepeatingKey(Keyboard::KeyPress::Key &key)
{
    std::string mapKey = asString(key);
    if (DEBUG)
        Serial.printf("Inserting key %c\n", mapKey);
    FutureKeyPress futureKeyPress = {key, millis()};
    repeatingKeys.insert({mapKey, futureKeyPress});
}

void KeyHandler::removeRepeatingKey(Keyboard::KeyPress::Key &key)
{
    std::string mapKey = asString(key);
    if (DEBUG)
        Serial.printf("Removing key %s\n", mapKey.c_str());
    repeatingKeys.erase(mapKey);
}

std::string KeyHandler::asString(Keyboard::KeyPress::Key &key)
{
    switch (key.type)
    {
    case Keyboard::KeyPress::KeyType::SINGLE:
        return std::string(1, key.character);
    case Keyboard::KeyPress::KeyType::MEDIA:
        return std::to_string(reinterpret_cast<uintptr_t>(key.mediaKey));
        break;
    }
    return std::string();
}