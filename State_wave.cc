#include "State_wave.h"
#include <iostream> // debugg

void State_wave::init()
{
    ;
}

void State_wave::handle_input()
{
    game.handle_input();
}

void State_wave::update_logic()
{
    game.update_logic();
}

void State_wave::render()
{
    game.render();
}

std::string State_wave::get_next_state()
{
    if ( game.get_health() <= 0)
    {
        window.close();
        return "end";
    }
    return this_state;
}
