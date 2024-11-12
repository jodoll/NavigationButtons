#include "NavigationPad.hpp"
#include <set>

using namespace NavigationPad;

class PressedStateDecorator
{
private:
    std::set<KeyCode> heldDownKeys;

public:
    Event onKeypadEvent(Event event);
};
