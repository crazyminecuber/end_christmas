#ifndef STATE_PAUSE_H
#define STATE_PAUSE_H
#include "State.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <memory> // shared_ptr
#include <string>

class State_pause : public State
{
public:
    State_pause(std::shared_ptr<sf::RenderWindow> _window,
        std::shared_ptr<Game> _game, 
        const sf::Font & _font);

    void init();

    void handle_input(sf::Event & event) override;
    void update_logic() override;
    void render()       override;

    int get_next_state() override;

private:
    bool unpause_game{false};

    /* graphics stuff below */
    sf::RectangleShape shader;
    sf::Text text_pause;
};

#endif // STATE_PAUSE_H
