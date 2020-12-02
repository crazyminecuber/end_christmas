#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H
#include <SFML/Graphics.hpp>
#include <map>
#include <string> 
#include "State.h"
#include "../Game.h"

/* Inspiration taken from Frida Flodin's: 
 * https://gitlab.ida.liu.se/TDDI82/Spelskelett
 * State_machine is the top layer of the game and controlls what part of the
 * game being run.
*/
class State_machine
{
public:
    State_machine(unsigned width, unsigned height);

    void run();

    bool running();

private:
    double fps{60};

    sf::RenderWindow window;

    Game game{};

    State* current_state;

    std::map<std::string, State*> states;

    bool _running{true};

    void throttle(double fps, sf::Clock & clock);

    // Changes next_state_ptr to states.at(state)
    void set_state(std::string const & state);

    // Gets the event and passes it over to the state
    void handle_events();

    void quit();

};
#endif