//TODO add color variables for background of shop and button?
//TODO change button size to only be the side length to guarantee it to be
//TODO place prictag and sprite resonable
//square?
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
    sf::Text heading{};

    sf::Text make_text();
    void generate_shop_grid(int nr_columns, sf::IntRect area); // Genera knappar med textur genom att kalla på tower_button många gånger.

};

// Can we make it position it self relative to its center point?
class Tower_button : public sf::RectangleShape
{
public:
    Tower_button(Tower * tw, Tower_shop * ts, sf::Vector2f & btn_size, sf::Vector2f & position);

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


