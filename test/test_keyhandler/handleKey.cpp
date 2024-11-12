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

TEST_F(KeyHandlerTest, ShouldReleaseKeyWhenKeymapReleasesKey)
{
    // Given
    sut.connect();
    sut.setKeyMap(keyMap);

    Event keyDownEvent = Event{KeyCode::ENTER, Event::Type::PRESSED};
    Event keyUpEvent = Event{KeyCode::ENTER, Event::Type::RELEASED};
    Key key = Key('D');
    EXPECT_CALL(keyMap, lookup(keyDownEvent))
        .WillOnce(Return(std::vector<Press>({Press{Press::Action::HOLD, 'D'}})));
    EXPECT_CALL(keyMap, lookup(keyUpEvent))
        .WillOnce(Return(std::vector<Press>({Press{Press::Action::RELEASE, 'D'}})));

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

TEST_F(KeyHandlerTest, ShoulSendKeyOnReleaseAfterKeyHasBeenReleased)
{
    // Given
    sut.connect();
    sut.setKeyMap(keyMap);

    Event keyDownEvent = Event{KeyCode::ENTER, Event::Type::PRESSED};
    Event keyUpEvent = Event{KeyCode::ENTER, Event::Type::RELEASED};
    Key keyEnter = Key('D');
    EXPECT_CALL(keyMap, lookup(keyDownEvent))
        .WillOnce(Return(std::vector<Press>({Press{Press::Action::HOLD, 'D'}})));
    EXPECT_CALL(keyMap, lookup(keyUpEvent))
        .WillOnce(Return(std::vector<Press>({Press{Press::Action::INSTANT, 'D'}})));

    // Then
    EXPECT_CALL(wrapper, holdKey(keyEnter)).Times(1);
    EXPECT_CALL(wrapper, writeKey(keyEnter)).Times(1);

    // When
    sut.handle(keyDownEvent);
    sut.handle(keyUpEvent);
}

TEST_F(KeyHandlerTest, ShouldReleaseAPressedKeyBeforeSendingItAgain)
{
    // Given
    sut.connect();
    sut.setKeyMap(keyMap);

    Event keyDownEvent = Event{KeyCode::ENTER, Event::Type::PRESSED};
    Event keyUpEvent = Event{KeyCode::ENTER, Event::Type::RELEASED};
    Key keyEnter = Key('D');
    EXPECT_CALL(keyMap, lookup(keyDownEvent))
        .WillOnce(Return(std::vector<Press>({Press{Press::Action::HOLD, 'D'}})));
    EXPECT_CALL(keyMap, lookup(keyUpEvent))
        .WillOnce(Return(std::vector<Press>({Press{Press::Action::INSTANT, 'D'}})));

    // Then
    {
        InSequence seq;
        EXPECT_CALL(wrapper, holdKey(keyEnter)).Times(1);
        EXPECT_CALL(wrapper, releaseKey(keyEnter)).Times(1);
        EXPECT_CALL(wrapper, writeKey(keyEnter)).Times(1);
    }

    // When
    sut.handle(keyDownEvent);
    sut.handle(keyUpEvent);
}

TEST_F(KeyHandlerTest, shouldReleaseKeysOnKeymapChange)
{
    // Given
    sut.connect();
    sut.setKeyMap(keyMap);

    Event keyUpEvent = Event{KeyCode::ENTER, Event::Type::RELEASED};
    Key keyEnter = Key('D');
    EXPECT_CALL(keyMap, lookup(keyUpEvent))
        .WillOnce(Return(std::vector<Press>({Press{Press::Action::HOLD, 'D'}})));

    // Then
    EXPECT_CALL(wrapper, holdKey(keyEnter)).Times(1);
    EXPECT_CALL(wrapper, releaseAll()).Times(1);

    // When
    sut.handle(keyUpEvent);
    sut.setKeyMap(keyMap);
}

TEST_F(KeyHandlerTest, shouldNotReleaseKeysAgainAfterKeymapChange)
{
    // Given
    sut.connect();
    sut.setKeyMap(keyMap);

    Event keyUpEvent = Event{KeyCode::ENTER, Event::Type::RELEASED};
    Key keyEnter = Key('D');
    EXPECT_CALL(keyMap, lookup(keyUpEvent))
        .WillRepeatedly(Return(std::vector<Press>({Press{Press::Action::HOLD, 'D'}})));

    // Then
    EXPECT_CALL(wrapper, holdKey(keyEnter)).Times(2);
    EXPECT_CALL(wrapper, releaseAll()).Times(1);
    EXPECT_CALL(wrapper, releaseKey(keyEnter)).Times(0);

    // When
    sut.handle(keyUpEvent);
    sut.setKeyMap(keyMap);
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

class ParametrizedByEventType :
    public KeyHandlerTest,
    public testing::WithParamInterface<Event::Type> {
};

INSTANTIATE_TEST_SUITE_P(AllEventTypes,
                         ParametrizedByEventType,
                         testing::Values(Event::PRESSED, Event::RELEASED, Event::RELEASED_HOLD, Event::HOLD));


TEST_P(ParametrizedByEventType, ShouldPassThrougAllKeyPadEvents)
{
    // Given
    sut.connect();
    sut.setKeyMap(keyMap);

    Event event = Event{KeyCode::ENTER, GetParam()};
    EXPECT_CALL(keyMap, lookup(event))
        .WillOnce(Return(std::vector<Press>()));

    // When
    sut.handle(event);
}
