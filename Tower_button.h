#ifndef TOWER_BUTTON_H
#define TOWER_BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Tower.h"
#include "Tower_shop.h"
#include "Wallet.h"

// Can we make it position it self relative to its center point?
class Tower_button : public sf::RectangleShape
{
public:
    Tower_button(Tower * tw, sf::Vector2f btn_size,
            sf::Vector2f position, sf::Color btn_color,sf::Color btn_select_color,
            sf::Color btn_no_cash_color, sf::Color font_color, std::string font_name);

    Tower * on_click(sf::Vector2f click, Wallet & wallet);
    void render(sf::RenderWindow & window);
    void update_ui(Wallet wallet);

private:
    void select();
    void unselect();
    void not_enough_cash();

    bool inactive{};
    bool selected{false};
    Tower* tower;
    sf::Text pricetag{};
    sf::Sprite tower_pic{};
    sf::Text make_pricetag(Tower * tw, std::string font_name);
    sf::Sprite make_tower_pic(Tower * tw);
    sf::Color color{};
    sf::Color select_color{};
    sf::Color no_cash_color{};
    sf::Color font_color{};

    sf::Texture     const& copy_of_tower_texture;
    sf::Sprite      copy_of_tower_sprite;
    sf::CircleShape copy_of_tower_circleshape;

};

#endif
