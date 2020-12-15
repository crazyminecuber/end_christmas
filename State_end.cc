#include "State_end.h"
#include <string>
#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace std;

void State_end::draw_end_screen()
{
    on_resize();
}

void State_end::handle_input(sf::Event & event)
{
    if ( event.type == sf::Event::KeyPressed )
    {
        window->close ();
    }

    if ( event.type == sf::Event::Resized )
    {
        on_resize();
    }
}


void State_end::on_resize()
{
    /* background */
    background_sprite.setTexture(background_texture, false);
    sf::Vector2f size{background_sprite.getGlobalBounds().width,
                      background_sprite.getGlobalBounds().height};
    background_sprite.setOrigin(size.x / 2, size.y / 2);
    background_sprite.setScale((-(window->getSize().x * 1.0) / size.x),
                               (  window->getSize().y * 1.0) / size.y);
    background_sprite.setPosition(window->getSize().x / 2.f,
                                  window->getSize().y / 2.f);

    /* text */
    string file{"resources/fonts/Christmas_Bell.otf"};
    if (!font.loadFromFile(file))
    {
        throw invalid_argument("Unable to load " + file);
    }
    string str1{""};
    string str2{""};

    if(game->player_has_won())
    {
        str1 = "You won!";

    }
    else
    {
        str1 = "Santa won!";
        str2 = "You got to level ";
        str2 += to_string(game->get_current_wave());
    }

    text1 = sf::Text{str1, font, 100};
    text2= sf::Text{str2, font, 80};

    sf::FloatRect bb_text1{text1.getGlobalBounds()};
    sf::FloatRect bb_text2{text2.getGlobalBounds()};
    sf::Vector2u window_size{window->getSize()};
    text1.setOrigin(bb_text1.width / 2.f, bb_text1.height / 2.f);
    text2.setOrigin(bb_text2.width / 2.f, bb_text2.height / 2.f);

    text1.setPosition(window_size.x / 2.f, window_size.y / 6.f);
    text2.setPosition(window_size.x / 2.f, window_size.y / 3.f);

    window->clear();

    /* put stuff to render here */
    window->draw(background_sprite);
    window->draw(text1);
    window->draw(text2);
    /*                          */
}


void State_end::update_logic()
{

}

void State_end::render()
{
    if(!first_render)

    {
        first_render = true;
        on_resize();
    }



    window->display();
}

int State_end::get_next_state()
{
    return END;
}
