#ifndef TOWER_SHOP_H
#define TOWER_SHOP_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Wallet.h"
#include "Tower.h"

class Tower_shop : public sf::RectangleShape
{
public:
    Tower_shop(std::vector<Tower *> pt, Wallet w, sf::Vector2f pos,
            sf::Vector2f siz, sf::Vector2f btn_size);
    Tower* chosen_tower;
    std::vector<sf::Drawable*> drawable{};
private:
    std::vector<Tower *> passive_towers;
    Wallet wallet;
    sf::Vector2f button_size;
    void generate_shop_grid(); // Genera knappar med textur genom att kalla på tower_button många gånger.
};

class Tower_button : public sf::RectangleShape
{
public:
    Tower_button(Tower * tw, Tower_shop * ts, sf::Vector2f btn_size);

    void on_click();

private:
    Tower* tower;
    Tower_shop* tower_shop;
    sf::Text pricetag;
    sf::Sprite tower_pic;
    sf::Text make_pricetag(Tower * tw);
    sf::Sprite make_tower_pic(Tower * tw);

};
#endif


