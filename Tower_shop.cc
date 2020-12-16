#include "Tower_shop.h"
#include "Tower_button.h"
#include "Resource_manager.h"
#include <iostream>
using namespace std;

Tower_shop::Tower_shop(std::vector<Tower *> pt, sf::Vector2f pos,
        sf::Vector2f siz, sf::Vector2f btn_size, sf::Color color,
        sf::Color btn_color, sf::Color btn_select_color,
        sf::Color btn_no_cash_color, sf::Color font_color,
        std::string font_name)
    : RectangleShape(siz), passive_towers{pt}, font_color{font_color}, button_size{btn_size},
    heading{make_text(font_name)}, wallet_text{make_text(font_name)}
// Lagra position och size i sfml:objectet.
{
    set_chosen_tower(nullptr);
    setPosition(pos);

    wallet_text.setPosition(getPosition().x + getGlobalBounds().width / 2, getPosition().y + 100);

    heading.setCharacterSize(70);
    heading.setFillColor(font_color);
    heading.setPosition(getPosition().x + getGlobalBounds().width / 2, getPosition().y);
    sf::Vector2f head_orig{};
    sf::FloatRect head_rec = heading.getLocalBounds();
    head_orig.x = head_rec.left + head_rec.width / 2;
    head_orig.y = -10.0f;
    heading.setOrigin(head_orig);

    int nr_columns{2};
    sf::IntRect area{int(getPosition().x),int(getPosition().y) + 130, int(siz.x), 400};
    generate_shop_grid(nr_columns, area, btn_color, btn_select_color, btn_no_cash_color, font_name);

    cout << "Shop created" << endl;
}

// Make a button for every tower
void Tower_shop::generate_shop_grid(int nr_columns, sf::IntRect area, sf::Color btn_color,
        sf::Color btn_select_color, sf::Color btn_no_cash_color, string font_name) // Genera knappar med textur genom att kalla på tower_button många gånger.
{

    /*
     * Calculates spacing between buttons to be used, given the area where the
     * buttons are going to go, and the size of the buttons. From this it places
     * them correctly. The reference point is in the geometrical center of the
     * button.
     */
    int spacing = (area.width - nr_columns * button_size.x) / (nr_columns + 1);
    int current_column{0};
    int current_row{0};
    sf::Vector2f btn_pos{0,0};
    for (auto tow_it = passive_towers.begin();
         tow_it != passive_towers.end();
         tow_it++)
    {
        btn_pos.x = area.left + button_size.x / 2 + spacing
                    + (current_column * (spacing + button_size.x));
        btn_pos.y = area.top + button_size.y / 2 + spacing
                    + (current_row * (spacing + button_size.y));
        buttons.push_back(Tower_button{*tow_it, button_size, btn_pos, btn_color, btn_select_color, btn_no_cash_color, font_color, font_name});
        current_column++;
        if (current_column >= nr_columns)
        {
            current_row++;
            current_column = 0;
        }
    }
}

sf::Text Tower_shop::make_text(string font_name)
{
    return sf::Text{"Tower Shop", Resource_manager::load_font(font_name)}; // Lite oeffektivt, men förhoppningvis så finns en flyttningkonstrutor.
}

void Tower_shop::render(sf::RenderWindow & window)
{
    // chose to render selected tower behind shop but maybe put in front?
    for (auto it = buttons.begin(); it != buttons.end(); it++)
    {
        it->render_selected_tower(window);
    }

    window.draw(*this);
    window.draw(wallet_text);
    window.draw(heading);

    for (auto it = buttons.begin(); it != buttons.end(); it++)
    {
        it->render_button(window);
    }
}

// Can probably be done way more efficiently
void Tower_shop::on_click(sf::Vector2f click, Wallet & wallet)
{
    // cout << "nullptr"<<endl;
    set_chosen_tower(nullptr);
    Tower * tw{};
    for (auto b = buttons.begin(); b != buttons.end(); b++)
    {
         tw = b->on_click(click, wallet);
         if (!(tw == nullptr))
         {
             set_chosen_tower(tw);
         }
    }
}

void Tower_shop::set_chosen_tower(Tower * tw)
{
    // cout << "set chosen_tower to: " << tw << endl;
    chosen_tower = tw;
}
Tower * Tower_shop::get_chosen_tower()
{
    // cout << "returning chosen tower: " << chosen_tower << endl;
    return chosen_tower;
}

void Tower_shop::update_shop_ui(Wallet wallet)
{
    wallet_text.setCharacterSize(50);
    wallet_text.setFillColor(font_color);
    wallet_text.setString("$" + to_string(wallet.getCash()));
    sf::Vector2f price_orig{};
    sf::FloatRect price_rec = wallet_text.getLocalBounds();
    price_orig.x = price_rec.left + price_rec.width / 2;
    price_orig.y = price_rec.top + price_rec.height / 2;
    wallet_text.setOrigin(price_orig);
    for (auto b = buttons.begin(); b != buttons.end(); b++)
    {
             b->update_ui(wallet);
    }
}
