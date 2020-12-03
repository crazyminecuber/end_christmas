#ifndef STATE_MENU_H
#define STATE_MENU_H
#include "State.h"
#include <string>

class State_menu : public State
{
public:
    State_menu(const std::string & title);
    void handle_event(sf::Event event) override;
    void update() override;
    void render(sf::RenderTarget & target) override;
    std::string get_next_state();
private:
    sf::Text title_text;
    sf::Text text;
    sf::Font font{};
    bool game{false};
};

#endif