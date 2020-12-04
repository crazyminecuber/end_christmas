#include "State_wait.h"
using namespace std;
    
State_wait::State_wait(sf::RenderWindow & win, Game & game)
    : window{win}, game{game}
{
    string file{"resources/fonts/Christmas_Bell.otf"};
    if (!font.loadFromFile(file))
    {
        throw invalid_argument("Unable to load " + file);
    }
    text_wait = sf::Text{"(Press P To Start Next Wave)", font, 60};
    sf::FloatRect bb_wait{text_wait.getGlobalBounds()};
    text_wait.setOrigin(bb_wait.width  / 2.f, bb_wait.height / 2.f);
    text_wait.setPosition(window.getSize().x * 0.5f, window.getSize().y *0.01f);

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

    window.draw(text_wait);

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
