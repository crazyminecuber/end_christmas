#ifndef STATE_MENU_H
#define STATE_MENU_H
#include "State.h"

class State_menu : public State
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