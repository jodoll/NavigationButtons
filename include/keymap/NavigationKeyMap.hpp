#include "keymap/Keyboard.hpp"


class NavigationKeyMap : public Keyboard::Map
{
private:
public:
    NavigationKeyMap() {};
    ~NavigationKeyMap() {};

    virtual std::vector<Keyboard::Press> lookup(KeyboardEvent::Event event);
};
