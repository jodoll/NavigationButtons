#include <stdint.h>

class PhysicalKeyboard
{
private:

public:
    virtual ~PhysicalKeyboard() {}
    virtual void scanKeys() = 0;
};
