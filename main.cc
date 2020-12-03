#include "State/State_machine.h"

int main()
{
    State_machine machine{"Kill Santa",1200,800};
    machine.run();
    return 0;
}