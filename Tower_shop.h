#ifndef TOWER_SHOP_H
#define TOWER_SHOP_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Wallet.h"
#include "Tower.h"

class Tower_shop : public sf::Sprite
{
public:
    Tower_shop(std::vector<Tower *> pt, Wallet w, sf::Vector2f pos,
            sf::Vector2f siz, sf::Vector2f btn_size, std::string texture_file,
            Wallet wallet )
        : passive_towers{pt}, wallet{w}, button_size{btn_size} // Lagra position och size i sfml:objectet.
    {
        chosen_tower = nullptr;
        generate_shop_grid();
    }
    Tower* chosen_tower;
private:
    sf::Vector2f button_size;
    std::vector<Tower *> passive_towers;
    Wallet wallet;
    void generate_shop_grid(); // Genera knappar med textur genom att kalla på tower_button många gånger.
};

class Tower_button : public sf::Sprite
{
public:
    Tower_button(Tower * tw, std::string texture_file, Tower_shop * ts)
        : sf::Sprite(),
    tower{tw}, tower_shop{ts}
    {

    }

    void on_click()
    {
        // Set chosen tower i shop.
        // TODO Ändra sprite på något sätt.
        tower_shop->chosen_tower = tower;
    }

private:
    Tower* tower;
    Tower_shop* tower_shop;

};
#endif //ENTITY_H

