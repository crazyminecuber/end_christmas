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

State_machine::State_machine(const string &title,
                             const string &settings_file,
                             const string &entity_file)
    :   window{make_shared<sf::RenderWindow>( 
            (load_settings(settings_file),  // comma operator
             sf::VideoMode
                {settings["window"]["width"],
                 settings["window"]["height"]}
            ), 
            title, 
            sf::Style::Close
        )},
        game{make_shared<Game>(
                window, 
                settings["game"]["health_texture"], 
                settings["game"]["hp"] ) }
{   
    game->init_tiles(entity_file);
    sf::Font font{Resource_manager::load_font(settings["font"])};
    states.insert(
        make_pair(MENU, 
            make_unique<State_menu>(window, game, font, settings["menu"]))
        );
    states.insert(
        make_pair(WAVE, 
            make_unique<State_wave>(window, game, font))
        );
    states.insert(
        make_pair(WAIT,
            make_unique<State_wait>(window, game, font))
        );
    states.insert(make_pair(PAUSE, make_unique<State_pause>(window, game, font)));
    states.insert(make_pair(END, make_unique<State_end>(window, game, font, settings["end"])));

    //set initial state
    current_state = MENU;
}

bool State_machine::running()
{
    return _running && window->isOpen();
}

void State_machine::run()
{
    sf::Clock clock{};
    while ( running() )
    {
        handle_input();

        states.at(current_state)->update_logic();

        states.at(current_state)->render();

        current_state = states.at(current_state)->get_next_state();

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

void State_machine::handle_input()
{
    sf::Event event;

    while (window->pollEvent(event))
    {
        if ( event.type == sf::Event::Closed )
        {
            window->close ();
        }
        else
        {
        states.at(current_state)->handle_input(event);
        }

        if ( event.type == sf::Event::Resized )
        {
            for (auto it=states.begin(); it!=states.end(); ++it)
            {
                (*it).second->handle_input(event);
            }
        }
    }
}

void State_machine::quit()
{
    // what more?
    window->close();
}
