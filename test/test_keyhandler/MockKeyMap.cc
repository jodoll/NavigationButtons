#include <gmock/gmock.h>
#include "keyboard/Keyboard.hpp"

using namespace Keyboard;

class MockKeyMap : public KeyMap
{
public:
    MOCK_METHOD(std::vector<Press>, lookup, (NavigationPad::Event event), (override));
};
