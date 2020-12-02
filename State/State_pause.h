#ifndef STATE_PAUSE_H
#define STATE_PAUSE_H
#include "State.h"

class State_pause : public State
{
public:
    void handle_event(sf::Event event) override;
    void update() override;
    void render(sf::RenderTarget & target) override;
    std::string get_next_state();
private:
    sf::Text text;
    sf::Font font{};
};

#endif