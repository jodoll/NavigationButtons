#include "keyboard/Keyboard.hpp"


class NavigationKeyMap : public Keyboard::KeyMap
{
private:
public:
    NavigationKeyMap() {};
    ~NavigationKeyMap() {};

    virtual std::vector<Keyboard::Press> lookup(NavigationPad::Event event);
};