#ifndef HEALTH_H
#define HEALTH_H

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <memory> // shared_ptr
#include "Resource_manager.h"

class Health
{
public:
    Health() = delete;

    Health(std::shared_ptr<sf::RenderWindow> win, std::string texture_file, int hp)
    : window{win}, font{new sf::Font},
      texture_heart{Resource_manager::load(texture_file)},
      health{hp}
    {
        init();
    }

    void init();
    void render();
    void remove_1_health();
    void remove_n_health(int n);
    int  get_health();

private:
    void update_text_health();

    std::shared_ptr<sf::RenderWindow> window;
    sf::Font* font;
    sf::Texture const& texture_heart;
    sf::Sprite sprite_heart;
    sf::RectangleShape background;

    int health;
    sf::Text text_health;
};

#endif //HEALTH_H
