#include "KeyHandler.hpp"
#include "Flags.hpp"

NoopKeyMap KeyHandler::noopKeyMap = NoopKeyMap();

void KeyHandler::connect()
{
    wrapper.connect();
    ledController->indicateSelectedKeyMap(3);
}

void KeyHandler::setKeyMap(Keyboard::Map &keyMap)
{
    wrapper.releaseAll();
    currentKeyMap = &keyMap;
    ledController->indicateSelectedKeyMap(3);
}

void KeyHandler::handle(NavigationPad::Event event)
{
    if (DEBUG)
        Serial.printf("Event: Type=%d, Key=%d\n", event.type, event.key);

    if (event.type < NavigationPad::Event::Type::RELEASED)
        ledController->onKeyPressed();
    auto keyPresses = currentKeyMap->lookup(event);
    for (Keyboard::Press keyPress : keyPresses)
    {
        switch (keyPress.action)
        {
        case Keyboard::Press::Action::INSTANT:
            wrapper.sendKey(keyPress.key);
            break;
        case Keyboard::Press::Action::HOLD:
            wrapper.pressKey(keyPress.key);
            break;
        case Keyboard::Press::Action::REPEATING:
            addRepeatingKey(keyPress.key);
            break;
        case Keyboard::Press::Action::RELEASE:
            removeRepeatingKey(keyPress.key);
            wrapper.releaseKey(keyPress.key);
            break;
        }
    }
    if (event.type == NavigationPad::Event::Type::RELEASED)
        ledController->onKeyReleased();
}

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
            wrapper.sendKey(futurePress.key);
        }
    };
    lastTick = now;
}

void KeyHandler::addRepeatingKey(Keyboard::Key &key)
{
    std::string mapKey = key.asString();
    if (DEBUG)
        Serial.printf("Inserting key %c\n", mapKey.c_str());
    FutureKeyPress futureKeyPress = {key, millis()};
    repeatingKeys.insert({mapKey, futureKeyPress});
}

void KeyHandler::removeRepeatingKey(Keyboard::Key &key)
{
    std::string mapKey = key.asString();
    if (DEBUG)
        Serial.printf("Removing key %s\n", mapKey.c_str());
    repeatingKeys.erase(mapKey);
}
