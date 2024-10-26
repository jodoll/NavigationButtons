#include "KeyMap.hpp"


class NoopKeyMap : public Keyboard::KeyMap
{
private:
public:
    NoopKeyMap() {};
    ~NoopKeyMap() {};

    virtual std::vector<Keyboard::KeyPress> lookup(KeyboardEvent::Event event);
};
