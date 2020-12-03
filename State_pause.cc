#include "State_pause.h"
#include <string>

void State_pause::init()
{
    /* shader */
    sf::Vector2f window_size(window.getSize().x,
                             window.getSize().y);
    shader.setSize(window_size);
    shader.setFillColor(sf::Color(0, 0, 0, 140));
    shader.setPosition(0, 0);

    /* text */
    std::string file{"resources/fonts/Christmas_Bell.otf"};
    if (!font.loadFromFile(file))
    {
        throw std::invalid_argument("Unable to load " + file);
    }

    std::string str = "Pause";
    text_pause = sf::Text{'('+str+')', font, 100};
    sf::FloatRect bb_pause{text_pause.getGlobalBounds()};
    text_pause.setOrigin(bb_pause.width  / 2.f, bb_pause.height / 2.f);
    text_pause.setPosition(window_size.x / 2.f, window_size.y / 2.f);
}

void State_pause::handle_input()
{
    /* reset variables */
    unpause_game = false;

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
                    unpause_game = true;
                }
            }
        }
}

void State_pause::update_logic()
{
    ;
}

void State_pause::render()
{
    window.clear();

    /* put stuff to render here */
    game.render();
    window.draw(shader);
    window.draw(text_pause);
    /*                          */

    window.display();
}

std::string State_pause::get_next_state()
{
    if ( unpause_game )
    {
        std::cout << "Un-pausing" << std::endl;
        return "wave";
    }
    else
    {
        return this_state;
    }
}
