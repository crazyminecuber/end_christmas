#include "Tower_button.h"
using namespace sf;
using namespace std;
Tower_button::Tower_button(Tower * tw, Tower_shop * ts, Vector2f btn_size,
                            Vector2f position, sf::Color btn_color, sf::Color btn_select_color)
                            : RectangleShape{btn_size}, tower{tw}, tower_shop{ts}, pricetag{make_pricetag(tw)},
                                tower_pic{make_tower_pic(tw)}, color{btn_color}, select_color{btn_select_color}
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

    // Scaling sprite
    float sprite_x{btn_size.x * 0.8f};
    float sprite_y{btn_size.y * 0.8f};
    Vector2u old_size{tower_pic.getTexture()->getSize()};
    tower_pic.setScale(sprite_x / old_size.x, sprite_y / old_size.y);
    tower_pic.setOrigin(tower_pic.getLocalBounds().width / 2, tower_pic.getLocalBounds().height / 2); // OBS! In local coordinates! Take scale into account! Therefore using localbounds.

    tower_pic.setPosition(getPosition());
    /*
     cout << "text globalbounds" << pricetag.getGlobalBounds().width << ", " << pricetag.getGlobalBounds().height
     << ", " << pricetag.getGlobalBounds().left << ", " << pricetag.getGlobalBounds().top << endl;
     cout << "text localbounds, width: " << pricetag.getLocalBounds().width << ", height: " << pricetag.getLocalBounds().height
     << ", left: " << pricetag.getLocalBounds().left << ", top:" << pricetag.getLocalBounds().top << endl;
     */
     cout << "button global bounds" << getGlobalBounds().width << ", " << getGlobalBounds().height
     << ", " << getGlobalBounds().left << ", " << getGlobalBounds().top << endl;

}

void Tower_button::on_click(sf::Vector2f click)
{
    // Set chosen tower i shop.
     if(getGlobalBounds().contains(click))
     {
        select();
        tower_shop->chosen_tower = tower;
     }
     else
     {
         unselect();
     }
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
    if ( !texture->loadFromFile ("resources/textures/Christmas_tree.png") )
    {
        cout << "Unable to load texture" << endl;
    }
    return Sprite{*texture}; // Again hoping for move construction
}

void Tower_button::render(sf::RenderWindow & window)
{
    window.draw(*this);
    window.draw(tower_pic);
    window.draw(pricetag);
}

void Tower_button::select()
{
    setFillColor(select_color);
}

void Tower_button::unselect()
{
    setFillColor(color);
}

