#include "keyboard/Keyboard.hpp"


class NavigationKeyMap : public Keyboard::KeyMap
{
private:
public:
    NavigationKeyMap() {};
    ~NavigationKeyMap() {};

    std::vector<Keyboard::Press> lookup(NavigationPad::Event event) override;
};
