#ifndef STATE_END_H
#define STATE_END_H
#include "State.h"
#include "Game.h"
#include <SFML/Graphics.hpp>

class State_end : public State
{
public:
    State_end(sf::RenderWindow & win, Game & gme)
    : window{win}, game{gme},
      background_texture{Resource_manager::load(
                            "resources/textures/background_start_menu.png")}
    {
        init();
    };

    void init();

    void handle_input(sf::Event & event) override;
    void update_logic() override;
    void render()       override;

    std::string get_next_state() override;

private:
    sf::RenderWindow & window;
    Game & game;
    std::string this_state{"end"};

    /* graphics stuff below */
    sf::Texture background_texture;
    sf::Sprite background_sprite;
    sf::Text text1;
    sf::Text text2;
    sf::Font font;
};

#endif // STATE_END_H
