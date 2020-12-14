#ifndef STATE_WAVE_H
#define STATE_WAVE_H
#include "State.h"
#include "Game.h"

class State_wave : public State
{
public:
    State_wave(sf::RenderWindow & win, Game & game)
    : window{win}, game{game}
    {
        init();
    };

    void init();

    void handle_input(sf::Event & event) override;
    void update_logic()                  override;
    void render()                        override;

    std::string get_next_state()         override;

private:
    sf::RenderWindow & window;
    Game & game;
    std::string this_state{"wave"};
    bool pause_game{false};
};

#endif // STATE_WAVE_H
