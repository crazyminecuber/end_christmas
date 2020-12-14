#ifndef STATE_PAUSE_H
#define STATE_PAUSE_H
#include "State.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <string>

class State_pause : public State
{
public:
    State_pause(sf::RenderWindow & win, Game & gme)
    : window{win}, game{gme}
    {
        init();
    };

    void init();

    void handle_input(sf::Event & event) override;
    void update_logic()                  override;
    void render()                        override;

    std::string get_next_state() override;

private:
    void on_resize();
    
    sf::RenderWindow & window;
    Game & game;
    std::string this_state{"pause"};
    bool unpause_game{false};

    /* graphics stuff below */
    sf::RectangleShape shader;
    sf::Text text_pause;
    sf::Font font;
};

#endif // STATE_PAUSE_H
