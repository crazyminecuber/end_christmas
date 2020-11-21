#include "Tower_shop.h"
using namespace sf;
using namespace std;

Tower_shop::Tower_shop(std::vector<Tower *> pt, Wallet w, sf::Vector2f pos,
        sf::Vector2f siz, sf::Vector2f btn_size)
    : RectangleShape(siz), passive_towers{pt}, wallet{w}, button_size{btn_size},
    heading{make_text()}// Lagra position och size i sfml:objectet.
{
    setPosition(pos);
    chosen_tower = nullptr;
    // Set position of text. Gör smartare!
    heading.setPosition(Vector2f(150,150));
    generate_shop_grid();
}

void Tower_shop::generate_shop_grid(int nr_columns, IntRect area) // Genera knappar med textur genom att kalla på tower_button många gånger.
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

    int spacing = (area.width - nr_columns * button_size.x) / (nr_columns + 1);
    int current_column{1};
    int current_row{1};
    Vector2f btn_pos{};
    for (auto tow_it = passive_towers.begin();
         tow_it != passive_towers.end();
         tow_it++)
    {
        // Lokala eller globala koordinater?
        // Global for now
        btn_pos.x = area.left + spacing * (current_column) + button_size.x * current_column - 1 / 2 * button_size.x;
        btn_pos.y = area.top + spacing * (current_row) + button_size.x * current_row - 1 / 2 * button_size.y;
        Tower_button(*tow_it, this, button_size, btn_pos);

        current_column++;
        if (current_column > nr_columns)
        {
            current_row++;
            current_column = 1;
        }
    }

    // Simple one for debugging purposes. Only crates one tower button.
    //Tower_button(passive_towers.front(), this, button_size);
}

sf::Text Tower_shop::make_text()
{
    Font * font = new Font{}; // Minnesläcker!Bör nog laddas i game istället.
    if ( !font->loadFromFile ("resources/fonts/best_font.ttf") )
    {
        // kunde inte ladda typsnitt
        cout << "Unable to load font" << endl;
    }
    return Text{"Tower Shop", *font}; // Lite oeffektivt, men förhoppningvis så finns en flyttningkonstrutor.
}

//----------------------------------------------------------------------------

Tower_button::Tower_button(Tower * tw, Tower_shop * ts, Vector2f & btn_size,
                            Vector2f & position)
                            : RectangleShape{btn_size}, tower{tw}, tower_shop{ts}, pricetag{make_pricetag(tw)},
                                tower_pic{make_tower_pic(tw)}
{
    // Creates sprite for image of tower, font and text for pricetag and sets
    // background color
    pricetag.setPosition(100,100); // Make some smart calculatoins here

    // Scaling sprite
    float sprite_x{100}; // The size you acctually want.
    float sprite_y{100};
    Vector2u old_size{tower_pic.getTexture()->getSize()};
    tower_pic.setPosition(100, 100); // Do more fancy calculations here
    tower_pic.setScale(sprite_x / old_size.x, sprite_y / old_size.y);

    //Set background.
    setFillColor(Color{0,0,100}); // hard coded color, should change
    setOrigin(btn_size / 2.0f); // Center
    setPosition(position);

    tower_shop->drawable.push_back(this);
    tower_shop->drawable.push_back(&pricetag);
    tower_shop->drawable.push_back(&tower_pic);

}

void Tower_button::on_click()
{
    // Set chosen tower i shop.
    // TODO Ändra sprite på något sätt.
    tower_shop->chosen_tower = tower;
}

sf::Text Tower_button::make_pricetag(Tower * tw)
{
    Font * font = new Font{}; // Minnesläcker!Bör nog laddas i game istället.
    if ( !font->loadFromFile ("resources/fonts/best_font.ttf") )
    {
        // kunde inte ladda typsnitt
        cout << "Unable to load font" << endl;
    }
    string cost {to_string(tw->cost)};
    return Text{cost, *font}; // Lite oeffektivt, men förhoppningvis så finns en flyttningkonstrutor.
}

sf::Sprite Tower_button::make_tower_pic(Tower * tw)
{
    tw->getColor();
    //Texture const *  texture = tw->getTexture(); // Problem att den är konstant :(
    Texture * texture = new Texture(); // Yet another memory leak.
    if ( !texture->loadFromFile ("resources/textures/Santa.png") )
    {
        cout << "Unable to load texture" << endl;
    }
    return Sprite{*texture}; // Again hoping for move construction
}
