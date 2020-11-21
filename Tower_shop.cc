#include "Tower_shop.h"
using namespace sf;
using namespace std;

Tower_shop::Tower_shop(std::vector<Tower *> pt, Wallet w, sf::Vector2f pos,
        sf::Vector2f siz, sf::Vector2f btn_size)
    : RectangleShape(siz), passive_towers{pt}, wallet{w}, button_size{btn_size} // Lagra position och size i sfml:objectet.
{
    setPosition(pos);
    chosen_tower = nullptr;
    generate_shop_grid();
}

void Tower_shop::generate_shop_grid() // Genera knappar med textur genom att kalla på tower_button många gånger.
{
    // Just to test, will add more advanced stuff later.
    Tower_button(passive_towers.front(), this, button_size);
}

//----------------------------------------------------------------------------

Tower_button::Tower_button(Tower * tw, Tower_shop * ts, Vector2f btn_size)
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
