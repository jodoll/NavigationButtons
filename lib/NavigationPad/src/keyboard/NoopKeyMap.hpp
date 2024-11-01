#include "keyboard/Keyboard.hpp"

class NoopKeyMap : public Keyboard::KeyMap
{
public:
    NoopKeyMap() {};
    ~NoopKeyMap() {};

    std::vector<Keyboard::Press> lookup(NavigationPad::Event event) override
    {
        return std::vector<Keyboard::Press>();
    }
};
