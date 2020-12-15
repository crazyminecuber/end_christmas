#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory> // shared_ptr
#include <string>
#include "State.h"
#include "Game.h"
#include "json.hpp"

/* Inspiration taken from Frida Flodin's:
 * https://gitlab.ida.liu.se/TDDI82/Spelskelett
 * State_machine is the top layer of the game and controlls what part of the
 * game being run.
*/
class State_machine
{
public:
    State_machine(
        const std::string &title,
        const std::string & settings_file,
        const std::string & entity_file
        );

    void run();

    bool running();

    void static set_fps(float fps);
    float static get_fps();

private:
    void load_settings(const std::string & settings_file);

    nlohmann::json settings;

    float static fps;

    std::shared_ptr<sf::RenderWindow> window;

    std::shared_ptr<Game> game;

    int current_state;

    std::unordered_map<int, std::unique_ptr<State>> states;

    bool _running{true};

    void throttle(float fps, sf::Clock & clock);

    // Changes next_state_ptr to states.at(state)
    void set_state(int state);

    // Gets the event and passes it over to the state
    void handle_input();

    void quit();

};
#endif // STATE_MACHINE_H
