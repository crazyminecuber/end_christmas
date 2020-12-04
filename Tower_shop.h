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
#include "Tower_button.h"

class Tower_button;
class Tower_shop : public sf::RectangleShape
{
public:
    Tower_shop(){};
    Tower_shop(std::vector<Tower *> pt, Wallet w, sf::Vector2f pos,
            sf::Vector2f siz, sf::Vector2f btn_size, sf::Color color, sf::Color btn_color,sf::Color btn_select_color, std::string font_name);
    void render(sf::RenderWindow & window);
    void on_click(sf::Vector2f click);
    void set_chosen_tower(Tower * tw);
    Tower * get_chosen_tower();


private:
    std::vector<Tower *> passive_towers;
    Wallet wallet;
    sf::Vector2f button_size;
    sf::Text heading{};
    std::vector<Tower_button> buttons{};
    Tower* chosen_tower;

    sf::Text make_text(std::string font_name);
    void generate_shop_grid(int nr_columns, sf::IntRect area, sf::Color btn_color, sf::Color btn_select_color, std::string font_name); // Genera knappar med textur genom att kalla på tower_button många gånger.

};

#endif


