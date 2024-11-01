#include <stdint.h>

class PhysicalNavigationPad
{
private:

public:
    virtual ~PhysicalNavigationPad() {}
    virtual void scanKeys() = 0;
};
