#include "Tower_shop.h"
#include "Tower_button.h"
#include "Resource_manager.h"
#include <iostream>
using namespace std;

Tower_shop::Tower_shop(std::vector<Tower *> pt, Wallet w, sf::Vector2f pos,
        sf::Vector2f siz, sf::Vector2f btn_size, sf::Color color, sf::Color btn_color, sf::Color btn_select_color, std::string font_name)
    : RectangleShape(siz), passive_towers{pt}, wallet{w}, button_size{btn_size},
    heading{make_text(font_name)}// Lagra position och size i sfml:objectet.
{
    setPosition(pos);
    set_chosen_tower(nullptr);
    // Set position of text. Gör smartare!
    // Centered horizontally but top vertically
    heading.setPosition(getPosition().x + getGlobalBounds().width / 2, getPosition().y);
    cout << "made a shop" << endl;

    sf::Vector2f head_orig{};
    sf::FloatRect head_rec = heading.getLocalBounds();
    head_orig.x = head_rec.left + head_rec.width / 2;
    head_orig.y = 0.0f;
    heading.setOrigin(head_orig);

    int nr_columns{2};
    sf::IntRect area{int(getPosition().x),int(getPosition().y) + 100, int(siz.x), 400};
    generate_shop_grid(nr_columns, area, btn_color, btn_select_color, font_name);
    //drawable.push_back(this);
    setFillColor(color);

     //cout << "shop globalbounds, width: " << getGlobalBounds().width << ", height: " << getGlobalBounds().height
     //<< ", left: " << getGlobalBounds().left << ", top:" << getGlobalBounds().top << endl;
     //cout << "shop position, x: " << getPosition().x << ", y: " << getPosition().y << endl;
}

void Tower_shop::generate_shop_grid(int nr_columns, sf::IntRect area, sf::Color btn_color, sf::Color btn_select_color, string font_name) // Genera knappar med textur genom att kalla på tower_button många gånger.
{
    // Just to test, will add more advanced stuff later.
    // What determins all the sizes? The shop will have a given with. When it
    // has taken all the space for the text and potentiall other thing at the
    // top, a rectangle will be created that tower_buttons are allowed to be
    // placed in. Then we assume that we are given (or computed elsewere), the
    // number of collumns, the button size. Then the spacing can be calculated.

    // Idea! Given the width of the rectangle and the width of the button,
    // calculate the spacing between the center of each button and another
    // center of a button or the edge of the rectangle

    // Make a button for every tower
     cout << "button rectangle, width: " << area.width << ", height: " << area.height
     << ", left: " << area.left << ", top:" << area.top << endl;

    int spacing = (area.width - nr_columns * button_size.x) / (nr_columns + 1);
    int current_column{0};
    int current_row{0};
    sf::Vector2f btn_pos{0,0};
    for (auto tow_it = passive_towers.begin();
         tow_it != passive_towers.end();
         tow_it++)
    {
        // Lokala eller globala koordinater?
        // Global for now
        btn_pos.x = area.left + button_size.x / 2 + spacing
                    + (current_column * (spacing + button_size.x));
        cout << "btn_pos.x"<<btn_pos.x << endl;
        btn_pos.y = area.top + button_size.y / 2 + spacing
                    + (current_row * (spacing + button_size.y));
        buttons.push_back(Tower_button{passive_towers.front(), this, button_size, btn_pos, btn_color, btn_select_color, font_name});

        current_column++;
        if (current_column >= nr_columns)
        {
            current_row++;
            current_column = 0;
        }
    }

    // Simple one for debugging purposes. Only crates one tower button.
    //Tower_button(passive_towers.front(), this, button_size);
}

sf::Text Tower_shop::make_text(string font_name)
{
    sf::Font * font = new sf::Font{}; // Minnesläcker!Bör nog laddas i game istället.
    return sf::Text{"Tower Shop", Resource_manager::load_font(font_name)}; // Lite oeffektivt, men förhoppningvis så finns en flyttningkonstrutor.
}

void Tower_shop::render(sf::RenderWindow & window)
{
    window.draw(*this);
    window.draw(heading);
    for (auto it = buttons.begin();
         it != buttons.end();
         it++)
    {
        it->render(window);
    }
}

// Can probably be done way more efficiently
void Tower_shop::on_click(sf::Vector2f click)
{
    cout << "Tower_shop passive_towers length" << passive_towers.size() << endl;
    //cout << "nullptr"<<endl;
    //set_chosen_tower(nullptr);
    for (auto b = buttons.begin(); b != buttons.end(); b++)
    {
         b->on_click(click);
    }
}

void Tower_shop::set_chosen_tower(Tower * tw)
{
    cout << "set chosen_tower to: " << tw << endl;
    chosen_tower = tw;
}
Tower * Tower_shop::get_chosen_tower()
{
    cout << "returning chosen tower: " << chosen_tower << endl;
    return chosen_tower;
}
