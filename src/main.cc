#include "State_machine.h"

int main()
{
    State_machine machine
    {
        "resources/settings.json", "resources/entity.json"
    };
    machine.run();
    return 0;
}
