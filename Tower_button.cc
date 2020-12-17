#include "Tower_button.h"
#include "Resource_manager.h"

using namespace sf;
using namespace std;


/*
 * Constructor for Tower_button. Initializes background color, text for showing
 * price, gets tower sprite from given tower, makes copy of sprite and setsa a
 * ring around it for using when placing towers.
 */
Tower_button::Tower_button(Tower * tw, Vector2f const & btn_size, Vector2f const & position,
        sf::Color const & btn_color, sf::Color const & btn_select_color, sf::Color const & btn_no_cash_color,
        sf::Color const & font_color, string const & font_name)
          : RectangleShape{btn_size}, tower{tw}, pricetag{make_pricetag(tw, font_name)},
            tower_pic{make_tower_pic(tw)}, color{btn_color}, select_color{btn_select_color},
            no_cash_color{btn_no_cash_color}, copy_of_tower_texture{*(tw->getTexture())}
{
    //Background
    setFillColor(btn_color);
    // Origin in center of shop.
    setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);
    setPosition(position);

    //Pricetag
    pricetag.setPosition(getPosition().x, getPosition().y + getLocalBounds().height * 0.3);
    // Set origin to middle in wierd way because SFML-text is offset for some
    // reason.
    Vector2f price_orig{};
    sf::FloatRect price_rec = pricetag.getLocalBounds();
    price_orig.x = price_rec.left + price_rec.width / 2;
    price_orig.y = price_rec.top + price_rec.height / 2;
    pricetag.setOrigin(price_orig);

    pricetag.setFillColor(font_color);
    pricetag.setCharacterSize(45);


    // Scale Tower sprite to btn_size
    float sprite_x{btn_size.x};
    float sprite_y{btn_size.y};
    Vector2u old_size{tower_pic.getTexture()->getSize()};
    tower_pic.setScale(sprite_x / old_size.x, sprite_y / old_size.y);
    tower_pic.setOrigin(tower_pic.getLocalBounds().width / 2, tower_pic.getLocalBounds().height / 2);

    tower_pic.setPosition(getPosition());

    // Initialize
    copy_of_tower_sprite.setTexture(copy_of_tower_texture, false);
    copy_of_tower_sprite.setScale(tower->getScale());
    copy_of_tower_sprite.setOrigin(tower->getOrigin());
    copy_of_tower_circleshape = tower->circle_hit_rad;
}

/*
 * Returns tower in the button when called givent, enough money.
 */

Tower * Tower_button::on_click(sf::Vector2f click, Wallet & wallet)
{
    Tower* returned_tower{nullptr};

    if ( wallet.getCash() < tower->cost )
    {
       not_enough_cash();
    }
    else if ( !getGlobalBounds().contains(click) || selected )
    {
       unselect();
    }
    else
    {
        select();
        returned_tower = tower;
    }
    return returned_tower;
}

/*
 * Helper function used in initalisation list to make a pricetag.
 */
sf::Text Tower_button::make_pricetag(Tower * tw, std::string const & font_name)
{
    string cost {to_string(tw->cost)};
    return Text{cost, Resource_manager::load_font(font_name)}; // Lite oeffektivt, men förhoppningvis så finns en flyttningkonstrutor.
}


/*
 * Helper function used in initalisation list to make a sprite to show the
 * tower.
 */
sf::Sprite Tower_button::make_tower_pic(Tower * tw)
{
    std::string texture_file{tw->get_texture_file()};
    return Sprite{Resource_manager::load(texture_file)}; // Again hoping for move construction
}


/*
 * Custom render functin that renders all alements in the button. Also calls
 * render function for rendering the selected tower under the cursor.
 */
void Tower_button::render_button(sf::RenderWindow & window)
{
    window.draw(*this);
    window.draw(tower_pic);
    window.draw(pricetag);
    render_selected_tower(window);
}


/*
 * Draws a sprite of the selected tower where the players mouse cursor is.
 */
void Tower_button::render_selected_tower(sf::RenderWindow & window)
{
    if ( selected )
    {
        copy_of_tower_sprite.setPosition     (sf::Mouse::getPosition(window).x,
                                              sf::Mouse::getPosition(window).y);
        copy_of_tower_circleshape.setPosition(sf::Mouse::getPosition(window).x,
                                              sf::Mouse::getPosition(window).y);
        window.draw(copy_of_tower_sprite);
        window.draw(copy_of_tower_circleshape);
    }
}

/*
 * Uppdates button state upon called. Specifically the color of the button so
 * that it reflekt current conditions. Should only be called when the amount of
 * cash has changed
 */
void Tower_button::update_ui(Wallet wallet)
{
    if (wallet.getCash() < tower->cost)
    {
       not_enough_cash();
    }
    else if (!selected)
    {
       unselect();
    }
}

/*
 * Helper functions for setting color and selected correctly.
 */

void Tower_button::select()
{
    setFillColor(select_color);
    selected = true;
}


void Tower_button::unselect()
{
    setFillColor(color);
    selected = false;
}


void Tower_button::not_enough_cash()
{
    setFillColor(no_cash_color);
    selected = false;
}
