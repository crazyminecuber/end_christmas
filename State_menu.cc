#include "State_menu.h"
#include <memory> // shared_ptr
#include <iostream> // debugg
#include "Resource_manager.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

State_menu::State_menu(std::shared_ptr<sf::RenderWindow> _window,
                       std::shared_ptr<Game> _game,
                       const sf::Font & _font,
                       json & entity,
                       json & settings)
                       : State(_window, _game, _font),
                       entity{entity},
                       settings{settings},
                       background_texture{
                           Resource_manager::load(
                               settings["menu"]["background"])}
{
    /* text */
    string tmp_str{settings["menu"]["title"]};
    text_title = sf::Text{tmp_str, font, 100};
    tmp_str = settings["menu"]["welcome_text"];
    text = sf::Text{tmp_str, font, 50};

    /* map names */
    std::map<string, map<string, string>>::iterator it = game->maps.begin();
    text_map_1 = sf::Text{game->maps[(*it).first]["display_name"], font, 50};
    map1 = (*it).first;
    it++;
    text_map_2 = sf::Text{game->maps[(*it).first]["display_name"], font, 50};
    map2 = (*it).first;
    it++;
    text_map_3 = sf::Text{game->maps[(*it).first]["display_name"], font, 50};
    map3 = (*it).first;
    it++;
    text_map_4 = sf::Text{game->maps[(*it).first]["display_name"], font, 50};
    map4 = (*it).first;

    /* visuals */
    background_sprite.setTexture(background_texture, false);
    on_resize();
}

void State_menu::handle_input(sf::Event & event)
{
    if ( event.type == sf::Event::MouseButtonPressed )
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

void State_menu::update_logic()
{
    check_hover();
}

void State_menu::render()
{
    window->clear();

    window->draw(background_sprite);

    window->draw(text_title);
    window->draw(text);

    if ( hovering_map_1 )
        window->draw(button_map_1);
    if ( hovering_map_2 )
        window->draw(button_map_2);
    if ( hovering_map_3 )
        window->draw(button_map_3);
    if ( hovering_map_4 )
        window->draw(button_map_4);

    window->draw(text_map_1);
    window->draw(text_map_2);
    window->draw(text_map_3);
    window->draw(text_map_4);

    window->display();
}

int State_menu::get_next_state()
{
    int next_state{MENU};
    if ( start_game )
    {
        game->load_map(entity, settings);
        game->init_entities(entity);
        next_state = WAIT;
    }

    /* reset variables */
    start_game = false;
    return next_state;
}

void State_menu::handle_click(sf::Vector2f mouse_pos)
{
    if ( button_map_1.getGlobalBounds().contains(mouse_pos) )
    {
        game->set_selected_map(map1);
        start_game = true;
    }
    if ( button_map_2.getGlobalBounds().contains(mouse_pos) )
    {
        game->set_selected_map(map2);
        start_game = true;
    }
    if ( button_map_3.getGlobalBounds().contains(mouse_pos) )
    {
        game->set_selected_map(map3);
        start_game = true;
    }
    if ( button_map_4.getGlobalBounds().contains(mouse_pos) )
    {
        game->set_selected_map(map4);
        start_game = true;
    }
}

void State_menu::check_hover()
{
    hovering_map_1 = false;
    hovering_map_2 = false;
    hovering_map_3 = false;
    hovering_map_4 = false;
    sf::Vector2f mouse_pos(sf::Mouse::getPosition(*window).x,
                           sf::Mouse::getPosition(*window).y);
    if ( button_map_1.getGlobalBounds().contains(mouse_pos) )
        hovering_map_1 = true;
    if ( button_map_2.getGlobalBounds().contains(mouse_pos) )
        hovering_map_2 = true;
    if ( button_map_3.getGlobalBounds().contains(mouse_pos) )
        hovering_map_3 = true;
    if ( button_map_4.getGlobalBounds().contains(mouse_pos) )
        hovering_map_4 = true;
}

void State_menu::on_resize()
{
    sf::Vector2u  window_size{window->getSize()};

    /* text */
    sf::FloatRect bb_title{text_title.getGlobalBounds()};
    text_title.setOrigin(bb_title.width / 2.f, bb_title.height / 2.f);
    text_title.setPosition(window_size.x / 2.f, window_size.y / 6.f);

    sf::FloatRect bb_text{text.getGlobalBounds()};
    text.setOrigin(bb_text.width / 2.f, bb_text.height / 2.f);
    text.setPosition(window_size.x / 2.f, window_size.y / 2.5);

    /* background */
    sf::Vector2f size{background_sprite.getGlobalBounds().width,
                      background_sprite.getGlobalBounds().height};
    background_sprite.setOrigin(size.x / 2, size.y / 2);
    background_sprite.setScale((
                    (-(window->getSize().x * 1.0) / size.x)
                    * background_sprite.getScale().x),
                    ( (window->getSize().y * 1.0) / size.y)
                    * background_sprite.getScale().y);
    background_sprite.setPosition(window->getSize().x / 2.f,
                                  window->getSize().y / 2.f);

    /* map buttons and text*/
    float button_side_length = 250;
    float gap = (window_size.x - (4 * button_side_length)) / 5;

    // button 1
    button_map_1.setSize(sf::Vector2f{ button_side_length,
                                      (button_side_length / 4)});
    button_map_1.setFillColor(sf::Color::Transparent);
    button_map_1.setOutlineThickness(4);
    button_map_1.setOutlineColor(sf::Color::Black);
    button_map_1.setPosition(gap,
                             window_size.y - (button_side_length / 4) - gap);
    sf::FloatRect bb_text_map_1{text_map_1.getGlobalBounds()};
    text_map_1.setFillColor(sf::Color::Black);
    text_map_1.setOrigin(bb_text_map_1.width  / 2.f,
                         bb_text_map_1.height / 2.f);
    text_map_1.setPosition(  button_map_1.getPosition().x
                           + button_side_length / 2.f,
                             button_map_1.getPosition().y
                           + button_side_length / 8.f - 12);

    // button 2
    button_map_2.setSize(sf::Vector2f{ button_side_length,
                                      (button_side_length / 4)});
    button_map_2.setFillColor(sf::Color::Transparent);
    button_map_2.setOutlineThickness(4);
    button_map_2.setOutlineColor(sf::Color::Black);
    button_map_2.setPosition(((2 * gap) + button_side_length),
                             window_size.y - (button_side_length / 4) - gap);
    sf::FloatRect bb_text_map_2{text_map_2.getGlobalBounds()};
    text_map_2.setFillColor(sf::Color::Black);
    text_map_2.setOrigin(bb_text_map_2.width  / 2.f,
                         bb_text_map_2.height / 2.f);
    text_map_2.setPosition(  button_map_2.getPosition().x
                           + button_side_length / 2.f,
                             button_map_2.getPosition().y
                           + button_side_length / 8.f - 12);

    // button 3
    button_map_3.setSize(sf::Vector2f{ button_side_length,
                                      (button_side_length / 4)});
    button_map_3.setFillColor(sf::Color::Transparent);
    button_map_3.setOutlineThickness(4);
    button_map_3.setOutlineColor(sf::Color::Black);
    button_map_3.setPosition(((3 * gap) + (2 * button_side_length)),
                             window_size.y - (button_side_length / 4) - gap);
    sf::FloatRect bb_text_map_3{text_map_3.getGlobalBounds()};
    text_map_3.setFillColor(sf::Color::Black);
    text_map_3.setOrigin(bb_text_map_3.width  / 2.f,
                         bb_text_map_3.height / 2.f);
    text_map_3.setPosition(  button_map_3.getPosition().x
                           + button_side_length / 2.f,
                             button_map_3.getPosition().y
                           + button_side_length / 8.f - 12);

    // button 4
    button_map_4.setSize(sf::Vector2f{ button_side_length,
                                      (button_side_length / 4)});
    button_map_4.setFillColor(sf::Color::Transparent);
    button_map_4.setOutlineThickness(4);
    button_map_4.setOutlineColor(sf::Color::Black);
    button_map_4.setPosition(((4 * gap) + (3 * button_side_length)),
                             window_size.y - (button_side_length / 4) - gap);
    sf::FloatRect bb_text_map_4{text_map_4.getGlobalBounds()};
    text_map_4.setFillColor(sf::Color::Black);
    text_map_4.setOrigin(bb_text_map_4.width / 2.f,
                         bb_text_map_4.height / 2.f);
    text_map_4.setPosition(  button_map_4.getPosition().x
                           + button_side_length / 2.f,
                             button_map_4.getPosition().y
                           + button_side_length / 8.f - 12);
}
