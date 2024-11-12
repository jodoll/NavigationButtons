#include "KeyHandler.hpp"
#include "ArduinoLog.h"

NoopKeyMap KeyHandler::noopKeyMap = NoopKeyMap();

void KeyHandler::setClock(Clock &clock)
{
    this->clock = &clock;
    this->lastTick = clock.currentTimeMillis();
}

void KeyHandler::connect()
{
    wrapper->connect();
    ledController->indicateSelectedKeyMap(3);
}

void KeyHandler::setKeyMap(Keyboard::KeyMap &keyMap)
{
    wrapper->releaseAll();
    currentKeyMap = &keyMap;
    ledController->indicateSelectedKeyMap(3);
}

void KeyHandler::handle(NavigationPad::Event event)
{
    Log.traceln("Event: Type=%d, Key=%d", event.type, event.key);

    if (event.type > NavigationPad::Event::Type::RELEASED)
    {
        ledController->onKeyPressed();
    }
    else
    {
        ledController->onKeyReleased();
    }

    auto keyPresses = currentKeyMap->lookup(event);
    for (Keyboard::Press keyPress : keyPresses)
    {
        releaseKeyIfPressed(keyPress.key);
        switch (keyPress.action)
        {
        case Keyboard::Press::Action::INSTANT:
            wrapper->writeKey(keyPress.key);
            break;
        case Keyboard::Press::Action::HOLD:
            pressedKeys.emplace(keyPress.key);
            wrapper->holdKey(keyPress.key);
            break;
        case Keyboard::Press::Action::REPEATING:
            addRepeatingKey(keyPress.key);
            break;
        case Keyboard::Press::Action::RELEASE:
            //key already released
            break;
        }
    }
}

void KeyHandler::tick()
{
    auto now = clock->currentTimeMillis();
    if (!repeatingKeysChanged && now < lastTick + 20)
        return;

    for (auto &entry : repeatingKeys)
    {
        auto &futurePress = entry.second;
        if (now >= futurePress.pressAfter)
        {
            auto remainingTimeToNextPress = repeatingKeyDelayMs - ((now - futurePress.pressAfter) % repeatingKeyDelayMs);
            futurePress.pressAfter += remainingTimeToNextPress;
            wrapper->writeKey(futurePress.key);
        }
    };
    lastTick = now;
    repeatingKeysChanged = false;
}

void KeyHandler::addRepeatingKey(Keyboard::Key &key)
{
    Log.verboseln("Inserting key %s", key.textValue.c_str());
    pressedKeys.emplace(key);
    FutureKeyPress futureKeyPress = {key, clock->currentTimeMillis()};
    repeatingKeys.insert({key, futureKeyPress});
    repeatingKeysChanged = true;
}

void KeyHandler::releaseKeyIfPressed(Keyboard::Key &key)
{
    if (pressedKeys.find(key) != pressedKeys.end())
    {
        pressedKeys.erase(key);
        wrapper->releaseKey(key);
        removeKeyIfRepeating(key);
    }
}

void KeyHandler::removeKeyIfRepeating(Keyboard::Key &key)
{
    if (repeatingKeys.count(key))
    {
        Log.verboseln("Removing key %s", key.textValue.c_str());
        repeatingKeys.erase(key);
        repeatingKeysChanged = true;
    }
}
