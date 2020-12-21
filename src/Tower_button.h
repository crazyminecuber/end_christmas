// TODO const and pointer or ref
// TODO något speciellt att tänka på vid intagning av pekare? För i de andra
// fallen vill man ju gärna ha konst ref.
// TODO more descriptive names for copy_of_tower_texture osv?

#ifndef TOWER_BUTTON_H
#define TOWER_BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Tower.h"
#include "Tower_shop.h"
#include "Wallet.h"

class Tower_button : public sf::RectangleShape
{
public:
    Tower_button(Tower * tw, sf::Vector2f const & btn_size, sf::Vector2f const & position,
            sf::Color const & btn_color, sf::Color const & btn_select_color, sf::Color const & btn_no_cash_color,
            sf::Color const & font_color, std::string const & font_name);

    Tower * on_click(sf::Vector2f const & click, Wallet & wallet);
    void render_button(sf::RenderWindow & window);
    void update_ui(Wallet const & wallet);

private:
    void select();
    void unselect();
    void not_enough_cash();
    sf::Text make_pricetag(Tower * tw, std::string const & font_name);
    sf::Sprite make_tower_pic(Tower * tw);
    void render_selected_tower(sf::RenderWindow & window);

    bool selected{false};
    Tower * tower{};
    sf::Text pricetag{};
    sf::Sprite tower_pic{};
    sf::Color color{};
    sf::Color select_color{};
    sf::Color no_cash_color{};

    sf::Texture const & copy_of_tower_texture{};
    sf::Sprite  copy_of_tower_sprite{};
    sf::CircleShape copy_of_tower_circleshape{};
};

#endif
