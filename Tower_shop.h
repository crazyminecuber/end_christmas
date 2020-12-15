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
    Tower_shop(std::vector<Tower *> pt, sf::Vector2f pos,
            sf::Vector2f siz, sf::Vector2f btn_size, sf::Color color,
            sf::Color btn_color,sf::Color btn_select_color, sf::Color btn_no_cash_color, sf::Color font_color, std::string font_name);
    void render(sf::RenderWindow & window);
    void on_click(sf::Vector2f click, Wallet & wallet);
    void set_chosen_tower(Tower * tw);
    Tower * get_chosen_tower();
    void update_shop_ui(Wallet wallet);


private:
    std::vector<Tower *> passive_towers;
    sf::Color font_color{};
    sf::Vector2f button_size;
    sf::Text heading{};
    sf::Text wallet_text{};
    std::vector<Tower_button> buttons{};
    Tower* chosen_tower;

    sf::Text make_text(std::string font_name);
    void generate_shop_grid(int nr_columns, sf::IntRect area, sf::Color btn_color, sf::Color btn_select_color, sf::Color btn_no_cash_color, std::string font_name); // Genera knappar med textur genom att kalla på tower_button många gånger.

};

#endif


