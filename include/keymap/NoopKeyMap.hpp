#include "keymap/Keyboard.hpp"

class NoopKeyMap : public Keyboard::Map
{
private:
public:
    NoopKeyMap() {};
    ~NoopKeyMap() {};

    virtual std::vector<Keyboard::Press> lookup(KeyboardEvent::Event event);
};
