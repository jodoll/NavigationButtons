#include "KeyMap.hpp"


class NavigationKeyMap : public Keyboard::KeyMap
{
private:
public:
    NavigationKeyMap() {};
    ~NavigationKeyMap() {};

    virtual std::vector<Keyboard::KeyPress> lookup(KeyboardEvent::Event event);
};
