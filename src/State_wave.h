#ifndef STATE_WAVE_H
#define STATE_WAVE_H
#include <SFML/Graphics.hpp>
#include <string>
#include <memory> // shared_ptr
#include "State.h"
#include "Game.h"

class State_wave : public State
{
public:
    State_wave(std::shared_ptr<sf::RenderWindow> _window,
               std::shared_ptr<Game> _game,
               const sf::Font & _font)
    : State(_window, _game, _font)
    {}

    void handle_input(sf::Event & event) override;
    void update_logic()                  override;
    void render()                        override;

    int  get_next_state()                override;

private:
    bool pause_game{false};
};

#endif // STATE_WAVE_H
