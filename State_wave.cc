#include "State_wave.h"
#include "State_machine.h"
#include <iostream> // debugg
using namespace std;
void State_wave::init()
{
    //game.create_1_enemy_basic();
}

void State_wave::handle_input(sf::Event & event)
{
    game.handle_input(event);
    if ( event.type == sf::Event::KeyPressed )
    {
        if ( event.key.code == sf::Keyboard::Escape )
        {
            pause_game = true;
        }
        else if ( event.key.code == sf::Keyboard::F )
        {
            if ( State_machine::get_fps() == 60 )
                State_machine::set_fps(120);
            else if ( State_machine::get_fps() == 120 )
                State_machine::set_fps(240);
            else
                State_machine::set_fps(60);
        }
    }

}

void State_wave::update_logic()
{
    game.update_logic();
}

void State_wave::render()
{
    window.clear();

    game.render();

    window.display();
}

string State_wave::get_next_state()
{
    string return_string{this_state};
    if ( game.get_health() <= 0)
    {
        return_string = "end";
    }
    else if ( pause_game )
    {
        return_string = "pause";
    }
    else if (game.player_has_won())
    {
        return_string = "end";
    }
    else if ( game.wave_complete() )
    {
        return_string = "wait";
    }
    /* reset variables */
    pause_game = false;
    return return_string;
}
