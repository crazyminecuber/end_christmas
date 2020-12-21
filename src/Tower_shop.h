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
    Tower_shop(std::vector<Tower *> const & passive_towers,
        sf::Vector2f const & pos, sf::Vector2f const & siz, sf::Vector2f const & btn_size,
        sf::Color const & btn_color, sf::Color const & btn_select_color,
        sf::Color const & btn_no_cash_color, sf::Color const & font_color,
        std::string const & font_name, std::string const & font_btn_name,
        std::string const & texture_file);
    void render(sf::RenderWindow & window);
    void on_click(sf::Vector2f const & click, Wallet & wallet);
    void set_chosen_tower(Tower * tw);
    Tower * get_chosen_tower() const;
    void update_shop_ui(Wallet const & wallet);

private:
    sf::Text make_text(std::string const & font_name);
    void generate_shop_grid(int nr_columns, int nr_rows, sf::IntRect const & area,
        sf::Color const & btn_color,sf::Color const & btn_select_color,
        sf::Color const & btn_no_cash_color, sf::Color const & font_color,
        std::string const & font_name, std::vector<Tower*> const & passive_towers,
        sf::Vector2f const & btn_size);

    sf::Text heading{};
    sf::Text wallet_text{};
    std::vector<Tower_button> buttons{};
    Tower* chosen_tower{nullptr};


};

#endif
