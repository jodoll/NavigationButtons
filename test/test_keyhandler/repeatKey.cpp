#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "KeyHandler.hpp"
#include "MockLedController.cc"
#include "MockKeyboardWrapper.cc"
#include "MockKeyMap.cc"
#include "TestClock.cc"
#include "led/StatusLedController.hpp"

using namespace NavigationPad;
using namespace Keyboard;
using testing::An;
using testing::InSequence;
using testing::Return;

// The fixture for testing class Foo.
class RepeatingKeyHandlerTest : public testing::Test
{
protected:
    TestClock clock;
    MockLedController controller;
    MockKeyboardWrapper wrapper;
    MockKeyMap keyMap;
    KeyHandler sut = KeyHandler(controller, wrapper);

    void SetUp()
    {
        sut.setClock(clock);
        sut.connect();
        sut.setKeyMap(keyMap);
    }
};

TEST_F(RepeatingKeyHandlerTest, ShouldNotSendRepeatingKeyImmedeatly)
{
    // Given
    Event keyDownEvent = Event{KeyCode::ENTER, Event::Type::PRESSED};
    Key key = Key('D');
    EXPECT_CALL(keyMap, lookup(An<Event>()))
        .WillOnce(Return(std::vector<Press>({Press{Press::Action::REPEATING, 'D'}})));

    // Then
    EXPECT_CALL(wrapper, writeKey(key)).Times(0);

    // When
    sut.handle(keyDownEvent);
}

TEST_F(RepeatingKeyHandlerTest, ShouldSendRepeatingKeyInTick)
{
    // Given
    Event keyDownEvent = Event{KeyCode::ENTER, Event::Type::PRESSED};
    Key key = Key('D');
    EXPECT_CALL(keyMap, lookup(An<Event>()))
        .WillOnce(Return(std::vector<Press>({Press{Press::Action::REPEATING, 'D'}})));

    // Then
    EXPECT_CALL(wrapper, writeKey(key)).Times(1);

    // When
    sut.handle(keyDownEvent);
    sut.tick();
}

TEST_F(RepeatingKeyHandlerTest, ShouldNotSendRepeatingKeyAgainBeforeDelayExpired)
{
    // Given
    Event keyDownEvent = Event{KeyCode::ENTER, Event::Type::PRESSED};
    Key key = Key('D');
    EXPECT_CALL(keyMap, lookup(An<Event>()))
        .WillOnce(Return(std::vector<Press>({Press{Press::Action::REPEATING, 'D'}})));

    // Then
    EXPECT_CALL(wrapper, writeKey(key)).Times(1);

    // When
    sut.handle(keyDownEvent);
    sut.tick();
    clock.advanceBy(sut.repeatingKeyDelayMs - 1);
    sut.tick();
}

TEST_F(RepeatingKeyHandlerTest, ShouldSendRepeatingKeyAgainAfterDelay)
{
    // Given
    Event keyDownEvent = Event{KeyCode::ENTER, Event::Type::PRESSED};
    Key key = Key('D');
    EXPECT_CALL(keyMap, lookup(An<Event>()))
        .WillOnce(Return(std::vector<Press>({Press{Press::Action::REPEATING, 'D'}})));

    // Then
    EXPECT_CALL(wrapper, writeKey(key)).Times(2);

    // When
    sut.handle(keyDownEvent);
    sut.tick();
    clock.advanceBy(sut.repeatingKeyDelayMs);
    sut.tick();
}

TEST_F(RepeatingKeyHandlerTest, ShouldNotSendRepeatingKeyAfterRelease)
{
    // Given
    Event keyDownEvent = Event{KeyCode::ENTER, Event::Type::PRESSED};
    Event keyUpEvent = Event{KeyCode::ENTER, Event::Type::RELEASED};
    Key key = Key('D');
    EXPECT_CALL(keyMap, lookup(An<Event>()))
        .WillOnce(Return(std::vector<Press>({Press{Press::Action::REPEATING, 'D'}})))
        .WillRepeatedly(Return(std::vector<Press>()));

    // Then
    EXPECT_CALL(wrapper, writeKey(key)).Times(1);

    // When
    sut.handle(keyDownEvent);
    sut.tick();
    clock.advanceBy(sut.repeatingKeyDelayMs);
    sut.handle(keyUpEvent);
    sut.tick();
}