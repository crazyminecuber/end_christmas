#include "State_wait.h"
using namespace std;
void State_wait::handle_input(sf::Event & event)
{
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
    /* shop logic */;
}

void State_wait::render()
{
    /* shop */;
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
