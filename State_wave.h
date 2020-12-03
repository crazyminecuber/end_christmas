#ifndef STATE_WAVE_H
#define STATE_WAVE_H
#include "State.h"
#include "Game.h"

class State_wave : public State
{
public:
    State_wave(sf::RenderWindow & win, Game & gme)
    : window{win}, game{gme}
    {
        init();
    };

    void init();

    void handle_input() override;
    void update_logic() override;
    void render()       override;
    std::string get_next_state();

private:
    sf::RenderWindow & window;
    Game & game;
    std::string this_state{"wave"};
    bool pause_game{false};
};

#endif // STATE_WAVE_H
