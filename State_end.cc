#include "State_end.h"
#include <string>

void State_end::init()
{
    /* background */
    background_sprite.setTexture(background_texture, false);
    sf::Vector2f size{background_sprite.getGlobalBounds().width,
                      background_sprite.getGlobalBounds().height};
    background_sprite.setOrigin(size.x / 2, size.y / 2);
    background_sprite.setScale((-(window.getSize().x * 1.0) / size.x),
                               (  window.getSize().y * 1.0) / size.y);
    background_sprite.setPosition(window.getSize().x / 2.f,
                                  window.getSize().y / 2.f);

    /* text */
    std::string file{"resources/fonts/Christmas_Bell.otf"};
    if (!font.loadFromFile(file))
    {
        throw std::invalid_argument("Unable to load " + file);
    }

    std::string str1{"Santa won!"};
    std::string str2{"You got to level "};
    // str2 += game.get_level();
    str2 += "1";

    text1 = sf::Text{'('+str1+')', font, 100};
    text2= sf::Text{str2, font, 80};

    sf::FloatRect bb_text1{text1.getGlobalBounds()};
    sf::FloatRect bb_text2{text2.getGlobalBounds()};
    sf::Vector2u window_size{window.getSize()};
    text1.setOrigin(bb_text1.width / 2.f, bb_text1.height / 2.f);
    text2.setOrigin(bb_text2.width / 2.f, bb_text2.height / 2.f);

    text1.setPosition(window_size.x / 2.f, window_size.y / 6.f);
    text2.setPosition(window_size.x / 2.f, window_size.y / 3.f);
}

void State_end::handle_input(sf::Event & event)
{
    if ( event.type == sf::Event::KeyPressed )
    {
        window.close ();
    }
}

void State_end::update_logic()
{
    ;
}

void State_end::render()
{
    window.clear();

    /* put stuff to render here */
    window.draw(background_sprite);
    window.draw(text1);
    window.draw(text2);
    /*                          */

    window.display();
}

std::string State_end::get_next_state()
{
    return this_state;
}
