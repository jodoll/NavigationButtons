#include <gtest/gtest.h>
#include "navigationPad/PressedStateDecorator.hpp"

class ParametrizedByEventType :
    public testing::TestWithParam<Event::Type> {
};

INSTANTIATE_TEST_SUITE_P(PassThroughEventTypes,
                         ParametrizedByEventType,
                         testing::Values(Event::PRESSED, Event::RELEASED, Event::RELEASED_HOLD));


TEST_P(ParametrizedByEventType, ShouldPassThrougPressed){
    PressedStateDecorator testee;
    Event event = {PLUS, GetParam()};

    auto result = testee.onKeypadEvent(event);

    ASSERT_EQ(result, event);
}

TEST(PressedStateDecoratorTest, ShouldReturnReleasedHoldWhenKeyWasHeld){
    PressedStateDecorator testee;
    Event event = {PLUS, Event::HOLD};
    Event releaseEvent = {PLUS, Event::RELEASED};
    testee.onKeypadEvent(event);

    auto result = testee.onKeypadEvent(releaseEvent);

    ASSERT_EQ(result.key, event.key);
    ASSERT_EQ(result.type, Event::RELEASED_HOLD);
}

TEST(PressedStateDecoratorTest, ShouldReturnRegularReleaseAfterHeldKeyWasReleased){
    PressedStateDecorator testee;
    Event event = {PLUS, Event::HOLD};
    Event releaseEvent = {PLUS, Event::RELEASED};
    testee.onKeypadEvent(event);
    testee.onKeypadEvent(releaseEvent);

    auto result = testee.onKeypadEvent(releaseEvent);

    ASSERT_EQ(result.key, event.key);
    ASSERT_EQ(result.type, Event::RELEASED);
}

TEST(PressedStateDecoratorTest, ShouldReturnRegularReleaseAfterHeldKeyWasReleasedWithReleaseHold){
    PressedStateDecorator testee;
    Event holdEvent = {PLUS, Event::HOLD};
    Event pressEvent = {PLUS, Event::PRESSED};
    Event releaseHoldEvent = {PLUS, Event::RELEASED_HOLD};
    Event releaseEvent = {PLUS, Event::RELEASED};
    testee.onKeypadEvent(holdEvent);
    testee.onKeypadEvent(releaseHoldEvent);
    testee.onKeypadEvent(pressEvent);

    auto result = testee.onKeypadEvent(releaseEvent);

    ASSERT_EQ(result.key, releaseEvent.key);
    ASSERT_EQ(result.type, Event::RELEASED);
}

TEST(PressedStateDecoratorTest, ShouldReturnRegularReleaseWhenDifferentKeyIsHeld){
    PressedStateDecorator testee;
    Event holdEvent = {MINUS, Event::HOLD};
    Event releaseEvent = {PLUS, Event::RELEASED};
    testee.onKeypadEvent(holdEvent);

    auto result = testee.onKeypadEvent(releaseEvent);

    ASSERT_EQ(result.key, releaseEvent.key);
    ASSERT_EQ(result.type, Event::RELEASED);
}

TEST(PressedStateDecoratorTest, ShouldOnlyReleaseKeyWhenEventIsRelease){
    PressedStateDecorator testee;
    Event holdEvent = {MINUS, Event::HOLD};
    Event pressEvent = {MINUS, Event::PRESSED};
    testee.onKeypadEvent(holdEvent);

    auto result = testee.onKeypadEvent(pressEvent);

    ASSERT_EQ(result, pressEvent);
}