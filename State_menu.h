#ifndef STATE_MENU_H
#define STATE_MENU_H

#include <SFML/Graphics.hpp>
#include <string>
#include <memory> // shared_ptr
#include "State.h"
#include "Game.h"
#include "json.hpp"

class State_menu : public State
{
public:
    State_menu(std::shared_ptr<sf::RenderWindow> _window,
               std::shared_ptr<Game> _game,
               const sf::Font &_font,
               nlohmann::json &entity,
               nlohmann::json &settings);

    void handle_input(sf::Event & event) override;
    void update_logic()                  override;
    void render()                        override;

    int get_next_state()                 override;

private:
    nlohmann::json const& entity;
    nlohmann::json const& settings;

    void handle_click(sf::Vector2f mouse_pos);
    void check_hover();
    void on_resize();

    bool start_game{false};
    bool hovering_map_1{false};
    bool hovering_map_2{false};
    bool hovering_map_3{false};
    bool hovering_map_4{false};

    /* graphics stuff below */
    sf::Texture background_texture;
    sf::Sprite background_sprite;

    /* buttons */
    sf::RectangleShape button_map_1;
    sf::RectangleShape button_map_2;
    sf::RectangleShape button_map_3;
    sf::RectangleShape button_map_4;
    sf::Text text_map_1;
    sf::Text text_map_2;
    sf::Text text_map_3;
    sf::Text text_map_4;
    std::string map1;
    std::string map2;
    std::string map3;
    std::string map4;

    sf::Text text_title;
    sf::Text text;
    sf::Text keybindings_header;
    sf::Text keybindings;
};

#endif // STATE_MENU_H
