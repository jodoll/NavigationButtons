#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "KeyHandler.hpp"
#include "MockLedController.cc"
#include "MockKeyboardWrapper.cc"
#include "MockKeyMap.cc"
#include "led/StatusLedController.hpp"

using namespace NavigationPad;
using namespace Keyboard;
using testing::An;
using testing::InSequence;
using testing::Return;



// The fixture for testing class Foo.
class KeyHandlerTest : public testing::Test
{
protected:
    MockLedController controller;
    MockKeyboardWrapper wrapper;
    MockKeyMap keyMap;
    KeyHandler sut = KeyHandler(controller, wrapper);
};

TEST_F(KeyHandlerTest, ShouldIndicateKeyMapOnConnect)
{
    EXPECT_CALL(controller, indicateSelectedKeyMap(3));
    sut.connect();
}

TEST_F(KeyHandlerTest, ShouldConnectKeyboardOnConnect)
{
    EXPECT_CALL(wrapper, connect());
    sut.connect();
}

TEST_F(KeyHandlerTest, ShouldWriteInstantKey)
{
    sut.connect();
    sut.setKeyMap(keyMap);

    Event event = Event{KeyCode::ENTER, Event::Type::PRESSED};
    EXPECT_CALL(keyMap, lookup(event))
        .WillOnce(Return(std::vector<Press>({Press{Press::Action::INSTANT, 'D'}})));

    EXPECT_CALL(wrapper, writeKey(Key('D')));
    sut.handle(event);
}

TEST_F(KeyHandlerTest, ShouldHoldKey)
{
    // Given
    sut.connect();
    sut.setKeyMap(keyMap);

    Event keyDownEvent = Event{KeyCode::ENTER, Event::Type::PRESSED};
    Key key = Key('D');
    EXPECT_CALL(keyMap, lookup(An<Event>()))
        .WillOnce(Return(std::vector<Press>({Press{Press::Action::HOLD, 'D'}})));

    EXPECT_CALL(wrapper, holdKey(key)).Times(1);
    EXPECT_CALL(wrapper, releaseKey(key)).Times(0);

    // When
    sut.handle(keyDownEvent);
}

TEST_F(KeyHandlerTest, ShouldHoldAndReleaseKey)
{
    // Given
    sut.connect();
    sut.setKeyMap(keyMap);

    Event keyDownEvent = Event{KeyCode::ENTER, Event::Type::PRESSED};
    Event keyUpEvent = Event{KeyCode::ENTER, Event::Type::RELEASED};
    Key key = Key('D');
    EXPECT_CALL(keyMap, lookup(An<Event>()))
        .WillOnce(Return(std::vector<Press>({Press{Press::Action::HOLD, 'D'}})))
        .WillOnce(Return(std::vector<Press>()));

    // Then
    {
        InSequence seq;
        EXPECT_CALL(wrapper, holdKey(key)).Times(1);
        EXPECT_CALL(wrapper, releaseKey(key)).Times(1);
    }

    // When
    sut.handle(keyDownEvent);
    sut.handle(keyUpEvent);
}

#if defined(ARDUINO)
#include <Arduino.h>

void setup()
{
    Serial.begin(115200);
    ::testing::InitGoogleMock();
}

void loop()
{
    // Run tests
    if (RUN_ALL_TESTS())
        ;
    // sleep for 1 sec
    delay(1000);
}

#else
int main(int argc, char **argv)
{
    ::testing::InitGoogleMock(&argc, argv);
    if (RUN_ALL_TESTS())
        ;

    // Always return zero-code and allow PlatformIO to parse results
    return 0;
}
#endif