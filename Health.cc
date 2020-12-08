#include "Health.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm> // std::max

void Health::init()
{
    /* hearth */
    float size_heart{50};
    sprite_heart.setPosition(0, 0);
    sprite_heart.setTexture(texture_heart, false);
    sf::Vector2u size_original;
    size_original = texture_heart.getSize();
    sprite_heart.setScale(size_heart / size_original.x,
                          size_heart / size_original.y);

    /* text */
    if ( !font->loadFromFile("resources/fonts/font.ttf") )
    {
     std::cout << "Kunde inte ladda font" << std::endl;
    }
    text_health.setFont((*font));
    text_health.setFillColor(sf::Color::White);
    text_health.setPosition(size_heart * 1.2, 2);
    text_health.setCharacterSize(size_heart * 0.8);

    update_text_health();

    /* background */
    sf::Vector2f rect_size;
    rect_size.x = (sprite_heart.getGlobalBounds().width +
                    text_health.getGlobalBounds().width  ) * 1.17;
    rect_size.y = std::max(sprite_heart.getGlobalBounds().height,
                            text_health.getGlobalBounds().height) + 5;
    background.setSize(rect_size);
    background.setFillColor(sf::Color(128, 128, 128));
    background.setOutlineThickness(1);
    background.setPosition(background.getOutlineThickness(),
                           background.getOutlineThickness());
    background.setOutlineColor(sf::Color::Black);

}

void Health::render()
{
    window.draw(background);
    window.draw(sprite_heart);
    window.draw(text_health);
}

void Health::update_text_health()
{
    text_health.setString(std::to_string(health));
}

void Health::remove_1_health()
{
    health = std::max(0, health - 1);
    update_text_health();
}

void Health::remove_n_health(int n)
{
    health = std::max(0, health - n);
    update_text_health();
}

int Health::get_health()
{
    return health;
}
