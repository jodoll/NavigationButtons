#include <gmock/gmock.h>
#include "KeyboardWrapper.hpp"

class MockKeyboardWrapper : public KeyboardWrapper
{
public:
    MOCK_METHOD(void, connect, (), (override));
    MOCK_METHOD(void, writeKey, (const Keyboard::Key &key), (override));
    MOCK_METHOD(void, holdKey, (Keyboard::Key & key), (override));
    MOCK_METHOD(void, releaseKey, (Keyboard::Key & key), (override));
    MOCK_METHOD(void, releaseAll, (), (override));
};