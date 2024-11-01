#include "KeyHandler.hpp"
#include "ArduinoLog.h"


NoopKeyMap KeyHandler::noopKeyMap = NoopKeyMap();

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
        releaseKeys(event);
    }

    auto keyPresses = currentKeyMap->lookup(event);
    for (Keyboard::Press keyPress : keyPresses)
    {
        switch (keyPress.action)
        {
        case Keyboard::Press::Action::INSTANT:
            wrapper->writeKey(keyPress.key);
            break;
        case Keyboard::Press::Action::HOLD:
            pressedKeys[event.key].insert(keyPress.key);
            wrapper->holdKey(keyPress.key);
            break;
        case Keyboard::Press::Action::REPEATING:
            pressedKeys[event.key].insert(keyPress.key);
            addRepeatingKey(keyPress.key);
            break;
        }
    }
}

void KeyHandler::releaseKeys(NavigationPad::Event &event)
{
    std::set<Keyboard::Key> &keys = pressedKeys[event.key];
    for (Keyboard::Key key : keys)
    {
        removeRepeatingKey(key);
        wrapper->releaseKey(key);
    }
    keys.clear();
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
            wrapper->writeKey(futurePress.key);
        }
    };
    lastTick = now;
}

void KeyHandler::addRepeatingKey(Keyboard::Key &key)
{
    Log.verboseln("Inserting key %s", key.textValue.c_str());
    FutureKeyPress futureKeyPress = {key, millis()};
    repeatingKeys.insert({key, futureKeyPress});
}

void KeyHandler::removeRepeatingKey(Keyboard::Key &key)
{
    Log.verboseln("Removing key %s", key.textValue.c_str());
    repeatingKeys.erase(key);
}
