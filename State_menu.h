#ifndef STATE_MENU_H
#define STATE_MENU_H
#include "State.h"
#include <SFML/Graphics.hpp>
#include <string>

class State_menu : public State
{
public:
    State_menu(sf::RenderWindow & win, const std::string & title);

    void handle_input() override;
    void update_logic() override;
    void render()       override;

    void handle_click(sf::Vector2f mouse_pos);
    void check_hover();
    std::string get_next_state();

private:
    sf::RenderWindow & window;

    bool start_game{false};
    std::string this_state{"menu"};
    bool hovering_start{false};

    /* graphics stuff below */
    sf::Texture background_texture;
    sf::Sprite background_sprite;

    sf::RectangleShape start_button;

    sf::Text title_text;
    sf::Text text;
    sf::Font font{};
};

#endif
