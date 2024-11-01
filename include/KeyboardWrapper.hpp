#include "keyboard/Keyboard.hpp"

#ifndef KEYBOARD_WRAPPER
#define KEYBOARD_WRAPPER

class KeyboardWrapper
{
public:
    virtual void connect()= 0;
    virtual void writeKey(const Keyboard::Key &key)=0;
    virtual void holdKey(Keyboard::Key &key)=0;
    virtual void releaseKey(Keyboard::Key &key)=0;
    virtual void releaseAll()=0;
};

#endif