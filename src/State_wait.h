#ifndef STATE_WAIT_H
#define STATE_WAIT_H
#include <SFML/Graphics.hpp>
#include <memory> // shared_ptr
#include "State.h"
#include "Game.h"

class State_wait : public State
{
public:
    State_wait(std::shared_ptr<sf::RenderWindow> _window,
               std::shared_ptr<Game> _game,
               const sf::Font &_font)
    : State(_window, _game, _font)
    {
        on_resize();
    }

    void handle_input(sf::Event &event) override;
    void update_logic()                 override;
    void render()                       override;
    
    int  get_next_state()               override;

private:
    void on_resize();

    bool play{false};
    sf::Text text_wait;
};

#endif // STATE_WAIT_H
