#ifndef TOWER_BUTTON_H
#define TOWER_BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Tower.h"
#include "Tower_shop.h"
// Can we make it position it self relative to its center point?
//
class Tower_shop;
class Tower_button : public sf::RectangleShape
{
public:
    Tower_button(Tower * tw, Tower_shop * ts, sf::Vector2f btn_size,
            sf::Vector2f position, sf::Color btn_color,sf::Color btn_select_color, std::string font_name);

    void on_click(sf::Vector2f click);
    void render(sf::RenderWindow & window);
    void select();
    void unselect();

    Tower_shop* tower_shop;
private:
    Tower* tower;
    sf::Text pricetag{};
    sf::Sprite tower_pic{};
    sf::Text make_pricetag(Tower * tw, std::string font_name);
    sf::Sprite make_tower_pic(Tower * tw);
    sf::Color color{};
    sf::Color select_color{};

};

#endif
