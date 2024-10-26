#include "KeyHandler.hpp"

NoopKeyMap KeyHandler::noopKeyMap = NoopKeyMap();

void KeyHandler::connect()
{
    bleKeyboard.begin();
}

void KeyHandler::setKeyMap(Keyboard::KeyMap &keyMap)
{
    bleKeyboard.releaseAll();
    currentKeyMap = &keyMap;
}

void KeyHandler::handle(KeyboardEvent::Event event)
{
    auto keyPresses = currentKeyMap->lookup(event);
    for (Keyboard::KeyPress keyPress : keyPresses)
    {
        switch (keyPress.action)
        {
        case Keyboard::KeyPress::ActionType::INSTANT:
            sendKeys(keyPress);
            break;
        case Keyboard::KeyPress::ActionType::HOLD:
            pressKeys(keyPress);
            break;
        case Keyboard::KeyPress::ActionType::RELEASE:
            releaseKeys(keyPress);
            break;
        }
    }
}

void KeyHandler::releaseKeys(Keyboard::KeyPress &keyPress)
{
    switch (keyPress.type)
    {
    case Keyboard::KeyPress::KeyType::SINGLE:
        bleKeyboard.release(keyPress.character);
        break;
    case Keyboard::KeyPress::KeyType::MEDIA:
        bleKeyboard.release(*keyPress.mediaKey);
        break;
    }
}

void KeyHandler::pressKeys(Keyboard::KeyPress &keyPress)
{
    switch (keyPress.type)
    {
    case Keyboard::KeyPress::KeyType::SINGLE:
        bleKeyboard.press(keyPress.character);
        break;
    case Keyboard::KeyPress::KeyType::MEDIA:
        bleKeyboard.press(*keyPress.mediaKey);
        break;
    }
}

void KeyHandler::sendKeys(Keyboard::KeyPress &keyPress)
{
    switch (keyPress.type)
    {
    case Keyboard::KeyPress::KeyType::SINGLE:
        bleKeyboard.write(keyPress.character);
        break;
    case Keyboard::KeyPress::KeyType::MEDIA:
        bleKeyboard.write(*keyPress.mediaKey);
        break;
    }
}
