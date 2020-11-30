#ifndef STATE_H
#define STATE_H
#include <SFML/Graphics.hpp>

class State
{
public:
    virtual ~State() = default;

    virtual void handle_event(sf::Event event) = 0;
    virtual void update() = 0;
    virtual void render() = 0;
};

#endif