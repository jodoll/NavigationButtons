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
    EXPECT_CALL(keyMap, lookup(keyDownEvent))
        .WillOnce(Return(std::vector<Press>({Press{Press::Action::HOLD, 'D'}})));

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


TEST_F(KeyHandlerTest, ShouldHandleEventsWhileKeyIsPressed)
{
    // Given
    sut.connect();
    sut.setKeyMap(keyMap);

    Event enterEvent = Event{KeyCode::ENTER, Event::Type::PRESSED};
    Key keyA = Key('A');
    EXPECT_CALL(keyMap, lookup(enterEvent))
        .WillOnce(Return(std::vector<Press>({Press{Press::Action::HOLD, 'A'}})));

    Event backEvent = Event{KeyCode::BACK, Event::Type::PRESSED};
    Key keyD = Key('D');
    EXPECT_CALL(keyMap, lookup(backEvent))
        .WillOnce(Return(std::vector<Press>({Press{Press::Action::INSTANT, 'D'}})));

    // Then
    {
        InSequence seq;
        EXPECT_CALL(wrapper, holdKey(keyA)).Times(1);
        EXPECT_CALL(wrapper, releaseKey(keyA)).Times(0);
        EXPECT_CALL(wrapper, writeKey(keyD)).Times(1);
    }

    // When
    sut.handle(enterEvent);
    sut.handle(backEvent);
}


TEST_F(KeyHandlerTest, ShouldHandleEventsOnReleaseKey)
{
    // Given
    sut.connect();
    sut.setKeyMap(keyMap);

    Event keyDownEvent = Event{KeyCode::ENTER, Event::Type::PRESSED};
    EXPECT_CALL(keyMap, lookup(keyDownEvent))
        .WillOnce(Return(std::vector<Press>()));

    Event keyUpEvent = Event{KeyCode::ENTER, Event::Type::RELEASED};
    Key keyD = Key('D');
    EXPECT_CALL(keyMap, lookup(keyUpEvent))
        .WillOnce(Return(std::vector<Press>({Press{Press::Action::INSTANT, 'D'}})));

    // Then
    {
        InSequence seq;
        EXPECT_CALL(wrapper, writeKey(keyD)).Times(1);
    }

    // When
    sut.handle(keyDownEvent);
    sut.handle(keyUpEvent);
}

