#ifndef STATE_H
#define STATE_H
#include <SFML/Graphics.hpp>

/* Base class for the states.
 *
*/
class State
{
public:
    virtual ~State() = default;
    // handles all the user input
    virtual void handle_input(sf::Event & event) = 0;
    // handles all the logic each frame
    virtual void update_logic() = 0;
    // render what will be drawn to the window
    virtual void render()       = 0;
    virtual std::string get_next_state() = 0;
};

#endif
