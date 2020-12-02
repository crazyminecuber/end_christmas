#ifndef STATE_H
#define STATE_H
#include <SFML/Graphics.hpp>
#include <string>

/* Base class for the states. 
 * 
*/
class State
{
public:
    virtual ~State() = default;
    // handles all the user input
    virtual void handle_event(sf::Event event) = 0;
    // handles all the logic each frame
    virtual void update() = 0;
    // render what will be drawn to the window
    virtual void render(sf::RenderTarget & target) = 0;
    virtual std::string get_next_state() = 0;
};

#endif