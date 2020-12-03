#ifndef STATE_PAUSE_H
#define STATE_PAUSE_H
#include "State.h"

class State_pause : public State
{
public:
    void handle_input(sf::Event event) override;
    void update_logic() override;
    void render(sf::RenderTarget & target) override;
    std::string get_next_state();
private:
    sf::Text text;
    sf::Font font{};
};

#endif
