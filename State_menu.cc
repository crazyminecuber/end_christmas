#include "State_menu.h"
#include "Resource_manager.h"
#include <iostream> // debugg

using namespace std;

State_menu::State_menu(sf::RenderWindow & win, const string & title)
: window{win}, background_texture{
                    Resource_manager::load(
                        "resources/textures/background_start_menu.png")}
{
    /* text */
    std::string file{"resources/fonts/Christmas_Bell.otf"};
    if (!font.loadFromFile(file))
    {
        throw std::invalid_argument("Unable to load " + file);
    }

    text_title = sf::Text{'('+title+')', font, 100};
    text = sf::Text{"Click santa to start game", font, 50};

    sf::FloatRect bb_title{text_title.getGlobalBounds()};
    sf::FloatRect bb_text{text.getGlobalBounds()};
    sf::Vector2u window_size{window.getSize()};
    text_title.setOrigin(bb_title.width  / 2.f, bb_title.height / 2.f);
    text.setOrigin(      bb_text.width   / 2.f, bb_text.height  / 2.f);

    text_title.setPosition(window_size.x / 2.f, window_size.y / 6.f);
    text.setPosition(window_size.x / 2.f, window_size.y / 2.f);

    /* background */
    background_sprite.setTexture(background_texture, false);
    sf::Vector2f size{background_sprite.getGlobalBounds().width,
                      background_sprite.getGlobalBounds().height};
    background_sprite.setOrigin(size.x / 2, size.y / 2);
    background_sprite.setScale((-(window.getSize().x * 1.0) / size.x),
                               (  window.getSize().y * 1.0) / size.y);
    background_sprite.setPosition(window.getSize().x / 2.f,
                                  window.getSize().y / 2.f);

    /* start button */
    start_button.setSize(sf::Vector2f{400, 200});
    start_button.setFillColor(sf::Color::Transparent);
    start_button.setOutlineThickness(4);
    start_button.setPosition(670, 450);
    start_button.setOutlineColor(sf::Color::Black);
}

void State_menu::handle_input()
{
    start_game = false;
    sf::Event event;
    while ( window.pollEvent(event) )
    {
        if ( event.type == sf::Event::Closed )
        {
            window.close ();
        }
        else if ( event.type == sf::Event::MouseButtonPressed )
        {
            auto mouse { event.mouseButton };
            if ( mouse.button == sf::Mouse::Button::Left )
            {
                float mouseX = mouse.x;
                float mouseY = mouse.y;
                handle_click(sf::Vector2f{mouseX, mouseY});
            }
        }
    }
}

void State_menu::update_logic()
{
    check_hover();
}

void State_menu::render()
{
    window.clear();

    /* put stuff to render here */
    window.draw(background_sprite);
    if ( hovering_start )
        window.draw(start_button);
    window.draw(text_title);
    window.draw(text);
    /*                          */

    window.display();
}

string State_menu::get_next_state()
{
    if ( start_game )
    {
        cout << "Starting game" << endl;
        return "wave";
    }
    else
        return this_state;
}

void State_menu::handle_click(sf::Vector2f mouse_pos)
{
    if ( start_button.getGlobalBounds().contains(mouse_pos) )
    {
        start_game = true;
    }
}

void State_menu::check_hover()
{
    hovering_start = false;
    sf::Vector2f mouse_pos(sf::Mouse::getPosition(window).x,
                           sf::Mouse::getPosition(window).y);
    if ( start_button.getGlobalBounds().contains(mouse_pos) )
    {
        hovering_start = true;
    }
}
