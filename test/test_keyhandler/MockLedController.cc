#include <gmock/gmock.h>
#include "led/StatusLedController.hpp"

class MockLedController : public StatusLedController
{
public:
    MOCK_METHOD(void, onKeyPressed, (), (override));
    MOCK_METHOD(void, onKeyReleased, (), (override));
    MOCK_METHOD(void, indicateSelectedKeyMap, (uint8_t keyMapNr), (override));
    MOCK_METHOD(void, onMenuEntered, (), (override));
    MOCK_METHOD(void, onMenuLeft, (), (override));
    MOCK_METHOD(void, turnOn, (), (override));
    MOCK_METHOD(void, turnOff, (), (override));
};