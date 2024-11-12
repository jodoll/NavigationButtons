#include "PressedStateDecorator.hpp"

Event PressedStateDecorator::onKeypadEvent(Event event)
{
    if (event.type == Event::HOLD)
    {
        heldDownKeys.emplace(event.key);
    }

    if (event.type <= Event::RELEASED)
    {
        bool isHeldKey = heldDownKeys.find(event.key) != heldDownKeys.end();
        heldDownKeys.erase(event.key);

        if (isHeldKey)
            return {event.key, Event::RELEASED_HOLD};
    }

    return event;
}