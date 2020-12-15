#include "Tower_button.h"
#include "Resource_manager.h"

using namespace sf;
using namespace std;
Tower_button::Tower_button(Tower * tw, Vector2f btn_size,
            Vector2f position, sf::Color btn_color, sf::Color btn_select_color, sf::Color btn_no_cash_color, sf::Color _font_color, string font_name)
            : RectangleShape{btn_size}, tower{tw}, pricetag{make_pricetag(tw, font_name)},
            tower_pic{make_tower_pic(tw)}, color{btn_color}, select_color{btn_select_color}, no_cash_color{btn_no_cash_color}, font_color{_font_color},
            copy_of_tower_texture{*(tw->getTexture())}
{
    // Creates sprite for image of tower, font and text for pricetag and sets
    // background color

    //Set background.
    setFillColor(btn_color); // hard coded color, should change
    setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2); // Center
    setPosition(position);

    pricetag.setPosition(getPosition()); // Make some smart calculatoins here

    // Set origin to middle of text is uggly, because localbounds is offset for
    // some reason.
    Vector2f price_orig{};
    sf::FloatRect price_rec = pricetag.getLocalBounds();
    price_orig.x = price_rec.left + price_rec.width / 2;
    price_orig.y = price_rec.top + price_rec.height / 2;
    pricetag.setOrigin(price_orig);
    pricetag.setFillColor(font_color);

    // Scalingfontsprite
    float sprite_x{btn_size.x * 0.8f};
    float sprite_y{btn_size.y * 0.8f};
    Vector2u old_size{tower_pic.getTexture()->getSize()};
    tower_pic.setScale(sprite_x / old_size.x, sprite_y / old_size.y);
    tower_pic.setOrigin(tower_pic.getLocalBounds().width / 2, tower_pic.getLocalBounds().height / 2); // OBS! In local coordinates! Take scale into account! Therefore using localbounds.

    tower_pic.setPosition(getPosition());

    // copy tower visuals
    copy_of_tower_sprite.setTexture(copy_of_tower_texture, false);
    copy_of_tower_sprite.setScale(tower->getScale());
    copy_of_tower_sprite.setOrigin(tower->getOrigin());
    copy_of_tower_circleshape = tower->circle_hit_rad;
}

Tower * Tower_button::on_click(sf::Vector2f click, Wallet & wallet)
{
    // Return chosen_tower to shop.
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

sf::Text Tower_button::make_pricetag(Tower * tw, std::string font_name)
{
    string cost {to_string(tw->cost)};
    return Text{cost, Resource_manager::load_font(font_name)}; // Lite oeffektivt, men förhoppningvis så finns en flyttningkonstrutor.
}

sf::Sprite Tower_button::make_tower_pic(Tower * tw)
{
    std::string texture_file{tw->get_texture_file()};
    return Sprite{Resource_manager::load(texture_file)}; // Again hoping for move construction
}

void Tower_button::render_button(sf::RenderWindow & window)
{
    window.draw(*this);
    window.draw(tower_pic);
    window.draw(pricetag);
}

void Tower_button::render_selected_tower(sf::RenderWindow & window)
{
    if ( selected )
    {
        copy_of_tower_sprite.setPosition     (sf::Mouse::getPosition().x,
                                              sf::Mouse::getPosition().y - 32); // have to subtract cursor height for some reason
        copy_of_tower_circleshape.setPosition(sf::Mouse::getPosition().x,
                                              sf::Mouse::getPosition().y - 32); // have to subtract cursor height for some reason
        window.draw(copy_of_tower_sprite);
        window.draw(copy_of_tower_circleshape);
    }
}

void Tower_button::select()
{
    setFillColor(select_color);
    inactive = false;
    selected = true;
}

void Tower_button::unselect()
{
    setFillColor(color);
    inactive = false;
    selected = false;
}
void Tower_button::not_enough_cash()
{
    setFillColor(no_cash_color);
    inactive = true;
    selected = false; // line should not be needed but maybe?
}

void Tower_button::update_ui(Wallet wallet)
{
    if (wallet.getCash() < tower->cost)
    {
       not_enough_cash();
    }
    else if (inactive)
    {
       unselect();
    }
}
