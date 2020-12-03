#ifndef STATE_WAIT_H
#define STATE_WAIT_H
#include "State.h"

class State_wait : public State
{
public:
    State_wait(){};
    void handle_input(sf::Event event) override;
    void update_logic() override;
    void render(sf::RenderTarget & target) override;
    std::string get_next_state();

};

#endif // STATE_WAIT_H
