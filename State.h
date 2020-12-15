#ifndef STATE_H
#define STATE_H
#include <string>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <memory> // shared_ptr

// Global variables for the state classes
const int MENU{0};
const int WAVE{1};
const int WAIT{2};
const int PAUSE{3};
const int END{4};

/* Base class for the states.
 * Does not accept _window or _game to be nullptr in constructor.
*/
class State
{
public:
    State(std::shared_ptr<sf::RenderWindow> _window,
        std::shared_ptr<Game> _game, 
        const sf::Font & _font) 
        : font{_font}
    {
        if (_window && _game)
        {
            window = _window;
            game = _game;
        }
        else
        {
            throw std::invalid_argument(
                "nullptr to sf::RenderWindow or Game is not accepted in State");
        }
        
    }
    virtual ~State() = default;
    // handles all the user inpuet
    virtual void handle_input(sf::Event & event) = 0;
    // handles all the logic each frame
    virtual void update_logic() = 0;
    // render what will be drawn to the window
    virtual void render()       = 0;
    virtual int get_next_state() = 0;

protected:
    sf::Font font;
    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<Game> game;
};

#endif
