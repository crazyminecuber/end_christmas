#include "State_wave.h"
#include "State_machine.h"
#include <memory> // shared_ptr
#include <iostream> // debugg

using namespace std;

void State_wave::handle_input(sf::Event & event)
/* handles both general game input and specific state input */
{
    // game input
    game->handle_input(event);

    // state input
    if ( event.type == sf::Event::KeyPressed )
    {
        if ( event.key.code == sf::Keyboard::Escape )
        {
            pause_game = true;
        }
        else if ( event.key.code == sf::Keyboard::F )
        {
            // toggle between 3 different game speeds
            if ( State_machine::get_fps() < 60.1 )
                State_machine::set_fps(120.f);
            else if ( State_machine::get_fps() < 120.1 )
                State_machine::set_fps(240.f);
            else
                State_machine::set_fps(60.f);
        }
        else if ( event.key.code == sf::Keyboard::R )
        {
            // toggle showing tower_radii
            game->set_render_tower_radii(
                                         !(game->get_render_tower_radii())
                                        );
        }
    }

}

void State_wave::update_logic()
{
    game->update_logic();
}

void State_wave::render()
{
    window->clear();

    game->render();

    window->display();
}

int State_wave::get_next_state()
{
    int next_state{WAVE};
    if ( game->get_health() <= 0)
    {
        next_state = END;
    }
    else if ( pause_game )
    {
        next_state = PAUSE;
    }
    else if (game->player_has_won())
    {
        next_state = END;
    }
    else if ( game->wave_complete() )
    {
        next_state = WAIT;
    }

    /* reset variables */
    pause_game = false;
    return next_state;
}
