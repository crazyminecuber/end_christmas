#include "State_machine.h"

int main()
{
    State_machine machine
    {
        "Kill Santa", "resources/settings.json", "entity.json"
    };
    machine.run();
    return 0;
}
