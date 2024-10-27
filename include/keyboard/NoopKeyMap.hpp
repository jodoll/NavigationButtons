#include "keyboard/Keyboard.hpp"

class NoopKeyMap : public Keyboard::KeyMap
{
private:
public:
    NoopKeyMap() {};
    ~NoopKeyMap() {};

    virtual std::vector<Keyboard::Press> lookup(NavigationPad::Event event);
};
