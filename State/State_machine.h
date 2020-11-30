#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H
#include <SFML/Graphics.hpp>
#include <map>
#include <string> 
#include "State.h"

class State_machine
{
public:
    State_machine(unsigned width, unsigned height);

    void run(State* state);

private:
    bool running();

    void throttle(unsigned fps, sf::Clock & clock);

    State* current_state;

    std::map<std::string, State*> states;

    void next_state(std::string state);

    void update();

    void draw();

    void quit();

};
#endif