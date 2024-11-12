#include "keyboard/Keyboard.hpp"


class NavigationKeyMap : public Keyboard::KeyMap
{
private:
    std::vector<Keyboard::Press> single(NavigationPad::Event::Type action, Keyboard::Key shortPress);
    std::vector<Keyboard::Press> repeating(NavigationPad::Event::Type action, Keyboard::Key key);
    std::vector<Keyboard::Press> hold(NavigationPad::Event::Type action, Keyboard::Key key);
    std::vector<Keyboard::Press> alternative(NavigationPad::Event::Type action, Keyboard::Key shortPress, Keyboard::Key longPress);
    std::vector<Keyboard::Press> alternativeRepeating(NavigationPad::Event::Type action, Keyboard::Key shortPress, Keyboard::Key longPress);

public:
    NavigationKeyMap() {};
    ~NavigationKeyMap() {};

    std::vector<Keyboard::Press> lookup(NavigationPad::Event event) override;
};
