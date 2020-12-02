#ifndef STATE_WAVE_H
#define STATE_WAVE_H
#include "State.h"

class State_wave : public State
{
public:
    State_wave(){};
    void handle_event(sf::Event event) override;
    void update() override;
    void render(sf::RenderTarget & target) override;
    std::string get_next_state();
    
};

#endif