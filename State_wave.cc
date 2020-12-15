#include "State_wave.h"
#include <memory> // shared_ptr
#include <iostream> // debugg
using namespace std;

State_wave::State_wave(std::shared_ptr<sf::RenderWindow> _window, 
        std::shared_ptr<Game> _game,
    const sf::Font & _font)
: State(_window, _game, _font)
{}

void State_wave::handle_input(sf::Event & event)
{
    game->handle_input(event);
    if ( event.type == sf::Event::KeyPressed )
    {
        if ( event.key.code == sf::Keyboard::Escape )
        {
            pause_game = true;
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
    int return_value{WAVE};
    if ( game->get_health() <= 0)
    {
        return_value = END;
    }
    else if ( pause_game )
    {
        return_value = PAUSE;
    }
    else if ( game->wave_complete() )
    {
        return_value = WAIT;
    }
    /* reset variables */
    pause_game = false;
    return return_value;
}
