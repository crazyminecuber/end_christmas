#include "State_wait.h"
using namespace std;
    
State_wait::State_wait(sf::RenderWindow & win, Game & game)
    : window{win}, game{game}
{

}
void State_wait::handle_input(sf::Event & event)
{
    game.handle_input(event);
    if ( event.type == sf::Event::KeyPressed )
    {
        if ( event.key.code == sf::Keyboard::P )
        {
            play = true;
        }
    }
}

void State_wait::update_logic()
{
    /* logic */;
}

void State_wait::render()
{
    window.clear();

    game.render();

    window.display();
}

std::string State_wait::get_next_state()
{
    string return_string{this_state};
    if (play)
    {
        return_string = "wave";
    }
    play = false;
    return return_string;
}
