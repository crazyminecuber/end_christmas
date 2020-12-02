#ifndef STATE_WAIT_H
#define STATE_WAIT_H
#include "State.h"

class State_wait : public State
{
public:
    State_wait(){};
    void handle_event(sf::Event event) override;
    void update() override;
    void render(sf::RenderTarget & target) override;
    std::string get_next_state();
    
};

#endif