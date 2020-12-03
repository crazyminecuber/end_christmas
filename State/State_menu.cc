#include "State_menu.h"

using namespace std;

State_menu::State_menu(const string & title)
{
    string file{"resources/fonts/Christmas_Bell.otf"};
    if (!font.loadFromFile(file))
    {
        throw invalid_argument("Unable to load " + file);
    }
    title_text = sf::Text{'('+title+')',font,24};
    text = sf::Text{"Press P to start game",font,16};
}

void State_menu::handle_event(sf::Event event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::P)
        {
            game = true;
        }
    }
}

void State_menu::update()
{
    /* dummy */
}

void State_menu::render(sf::RenderTarget & target)
{
    sf::FloatRect text_bounds{text.getGlobalBounds()};
    sf::Vector2u window_size{target.getSize()};

    text.setPosition( (window_size.x - text_bounds.width) / 2,
                      (window_size.y - text_bounds.height) / 2);

    text_bounds = title_text.getGlobalBounds();
    title_text.setPosition( window_size.x / 4 - text_bounds.width / 2,
                            window_size.y / 4 - text_bounds.height / 2);
    target.draw(title_text);
    target.draw(text);
}

string State_menu::get_next_state()
{
    if (game)
    {
        return "wave";
    }
}
