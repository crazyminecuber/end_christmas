#ifndef STATE_MENU_H
#define STATE_MENU_H
#include "State.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <string>

class State_menu : public State
{
public:
    State_menu(sf::RenderWindow & win, Game & game, const std::string & title);

    void handle_input(sf::Event & event) override;
    void update_logic() override;
    void render()       override;

    std::string get_next_state() override;

private:
    void handle_click(sf::Vector2f mouse_pos);
    void check_hover();
    void window_calculations();
    sf::RenderWindow & window;
    Game & game;

    bool start_game{false};
    std::string this_state{"menu"};
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
    sf::Font font;
};

#endif // STATE_MENU_H
