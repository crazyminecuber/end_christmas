#ifndef STATE_WAIT_H
#define STATE_WAIT_H
#include "State.h"
#include "Game.h"

class State_wait : public State
{
public:
    State_wait(sf::RenderWindow & win, Game & game);
    void handle_input(sf::Event & event) override;
    void update_logic() override;
    void render() override;
    std::string get_next_state() override;

private:
    bool play{false};
    std::string this_state{"wait"};
    sf::Text text_wait;
    sf::Font font;
    sf::RenderWindow & window;
    Game & game;
};

#endif // STATE_WAIT_H
