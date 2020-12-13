#include "State_machine.h"
#include <utility>
#include <string>
#include "State_menu.h"
#include "State_wave.h"
#include "State_wait.h"
#include "State_pause.h"
#include "State_end.h"
#include "json.hpp"
#include <fstream>

using namespace std;
using json = nlohmann::json;

State_machine::State_machine(const string & title,
                             const string & settings_file,
                             const string & entity_file)
    :   window
        { 
            ( // comma operator
                load_settings(settings_file),
                sf::VideoMode
                {
                    settings["window"]["width"],
                    settings["window"]["height"]
                }
            ), 
            title, 
            sf::Style::Close
        },
        game{window, settings["game"]["health_texture"], settings["game"]["hp"]}
{   
    states.insert(
        make_pair("menu", new State_menu(window, game, title, entity_file)));
    states.insert(make_pair("wave", new State_wave(window, game)));
    states.insert(make_pair("wait", new State_wait(window, game)));
    states.insert(make_pair("pause", new State_pause(window, game)));
    states.insert(make_pair("end", new State_end(window, game)));

    //set initial state
    current_state = states.at("menu");
}

bool State_machine::running()
{
    return _running && window.isOpen();
}

void State_machine::run()
{
    sf::Clock clock{};
    while ( running() )
    {
        handle_input();

        current_state->update_logic();

        set_state(current_state->get_next_state());

        current_state->render();

        throttle(fps, clock);
    }
    quit();
}

void State_machine::load_settings(const string & settings_file)
{
    ifstream ifs{settings_file};
    if (ifs.is_open())
    {
        ifs >> settings;
        ifs.close();
    }
    else
    {
        throw invalid_argument("Could not open " + settings_file);
    }
}

void State_machine::throttle(const double fps, sf::Clock & clock)
{
    auto const target{sf::milliseconds(1000.0/fps)};
    auto wait_time{target - clock.getElapsedTime()};
    sleep(wait_time);
    clock.restart();
}

void State_machine::set_state(string const & state)
{
    current_state = states.at(state);
}

void State_machine::handle_input()
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        if ( event.type == sf::Event::Closed )
        {
            window.close ();
        }
        else
        {
        current_state->handle_input(event);
        }
    }
}

void State_machine::quit()
{
    // what more?
    window.close();
}
