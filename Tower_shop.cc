//TODO passive vs factories
#include "Tower_shop.h"
#include "Tower_button.h"
#include "Resource_manager.h"
#include <iostream>
using namespace std;
using namespace sf;

Tower_shop::Tower_shop(std::vector<Tower *> const & passive_towers, Vector2f const & pos,
    Vector2f const & siz, Vector2f const & btn_size, Color const & btn_color,
    Color const & btn_select_color,  Color const & btn_no_cash_color,
    Color const & font_color, std::string const & font_name,
    std::string const & font_btn_name, std::string const & texture_file)
        : RectangleShape(siz), heading{make_text(font_name)}, wallet_text{make_text(font_name)}
{
    // Background
    setPosition(pos);
    setTexture(&Resource_manager::load(texture_file));

    // Heading
    heading.setCharacterSize(60);
    heading.setFillColor(font_color);
    heading.setPosition(getPosition().x + getGlobalBounds().width / 2, getPosition().y + getGlobalBounds().height * 0.092);
    // Origion is geometrical center
    Vector2f head_orig{};
    FloatRect head_rec = heading.getLocalBounds();
    head_orig.x = head_rec.left + head_rec.width / 2;
    head_orig.y = head_rec.top + head_rec.height / 2;
    heading.setOrigin(head_orig);

    //Wallet
    wallet_text.setPosition(getPosition().x + getGlobalBounds().width / 2, getPosition().y + getGlobalBounds().height * 0.13);
    wallet_text.setCharacterSize(50);
    wallet_text.setFillColor(font_color);

    // The picture that we ended up going for is 2340 pixles high and we will
    // use the buttom four shelves for displaying the towers. The area to be
    // used in regular pixel coordinates will therefore be from 447 and be 1770
    // high.
    //
    // This could be done more dynamically but is a quick way to get it to look
    // nice.

    int nr_columns{2};
    float area_top_ratio{447.0f / 2340.0f};
    float area_height_ratio{(1770.0f / 2340.0f)* 0.97};
    IntRect area{int(getPosition().x), int(getPosition().y + siz.y * area_top_ratio),
        int(siz.x), int(siz.y * area_height_ratio)};
    generate_shop_grid(nr_columns, 4, area, btn_color, btn_select_color,
            btn_no_cash_color, font_color, font_btn_name, passive_towers, btn_size);
}


/*
 * Creates buttons in a grid. Calculates correct spacing in both the horizontal and
 * vertical.
 */
void Tower_shop::generate_shop_grid(int nr_columns, int nr_rows, IntRect const & area,
    Color const & btn_color, Color const & btn_select_color, Color const & btn_no_cash_color,
    Color const & font_color, string const & font_name, vector<Tower*> const & passive_towers,
    Vector2f const & button_size)
{
    int hor_spacing = (area.width - nr_columns * button_size.x) / (nr_columns + 1);
    int ver_spacing = area.height / nr_rows;
    int current_column{0};
    int current_row{0};
    Vector2f btn_pos{0,0};
    float ver_shift_ratio{0.7};

    for (auto tow_it = passive_towers.begin();
         tow_it != passive_towers.end();
         tow_it++)
    {
        btn_pos.x = area.left + button_size.x / 2 + hor_spacing
                    + (current_column * (hor_spacing + button_size.x));
        btn_pos.y = area.top + ver_spacing * ver_shift_ratio +
                    + (current_row * (ver_spacing));
        buttons.push_back(Tower_button{*tow_it, button_size, btn_pos, btn_color,
                btn_select_color, btn_no_cash_color, font_color, font_name});
        current_column++;
        if (current_column >= nr_columns)
        {
            current_row++;
            current_column = 0;
        }
    }
}


/*
 * Helper for intialization list
 */
Text Tower_shop::make_text(string font_name)
{
    return Text{"Tower Shop", Resource_manager::load_font(font_name)};
}


/*
 * Custom render that render the shop background, cash in wallet and calls the
 * renderfunction of all the buttons.
 */
void Tower_shop::render(RenderWindow & window)
{
    window.draw(*this);
    window.draw(wallet_text);
    window.draw(heading);

    // Draw every button
    for (auto it = buttons.begin(); it != buttons.end(); it++)
    {
        it->render_button(window);
    }
}


/*
 * Restore cheosen_tower and call on_click for every button and update
 * chosen_tower accordingly.
 */
void Tower_shop::on_click(Vector2f click, Wallet & wallet)
{
    // Restore chosen tower to nullptr first on every click. It might be set
    // again later in this function.
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


/*
 * Updates user interface of shop. Only needs to be called when money in wallet
 * has changed.
 */
void Tower_shop::update_shop_ui(Wallet wallet)
{
    //Re-center text.
    wallet_text.setString("$" + to_string(wallet.getCash()));
    Vector2f price_orig{};
    FloatRect price_rec = wallet_text.getLocalBounds();
    price_orig.x = price_rec.left + price_rec.width / 2;
    price_orig.y = price_rec.top + price_rec.height / 2;
    wallet_text.setOrigin(price_orig);

    // Update ui of each button.
    for (auto b = buttons.begin(); b != buttons.end(); b++)
    {
         b->update_ui(wallet);
    }
}


void Tower_shop::set_chosen_tower(Tower * tw)
{
    chosen_tower = tw;
}


Tower * Tower_shop::get_chosen_tower()
{
    return chosen_tower;
}
