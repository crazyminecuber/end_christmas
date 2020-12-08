#include "State_machine.h"

int main()
{
    State_machine machine{"Kill Santa", 1400, 800};
    machine.run();
    return 0;
}
