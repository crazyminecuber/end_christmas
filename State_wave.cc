#include "State_wave.h"
#include <iostream> // debugg

void State_wave::init()
{
    game.create_1_enemy_basic();
}

void State_wave::handle_input()
{
    /* reset variables */
    pause_game = false;

    sf::Event event;
    while (window.pollEvent(event))
        {
            if ( event.type == sf::Event::Closed )
            {
                window.close ();
            }
            if ( event.type == sf::Event::KeyPressed )
            {
                if ( event.key.code == sf::Keyboard::P )
                {
                    pause_game = true;
                }
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

std::string State_wave::get_next_state()
{
    if ( game.get_health() <= 0)
    {
        window.close(); // temporary
        return "end";
    }
    else if ( pause_game )
    {
        std::cout << "Pausing" << std::endl;
        return "pause";
    }
    else
    {
        return this_state;
    }
}
