#include "State_machine.h"
#include <utility>
#include <string>
#include "State_menu.h"
#include "State_wave.h"
//#include "State_wait.h"
#include "State_pause.h"
#include "State_end.h"

using namespace std;

State_machine::State_machine(const string & title,
                             unsigned width, unsigned height)
    : window{sf::VideoMode{width,height}, title},
      game{window, "map.csv", "entity.json", 100}
{
    states.insert(make_pair("menu", new State_menu(window, title)));
    states.insert(make_pair("wave", new State_wave(window, game)));
    //states.insert(make_pair("wait", new State_wait));
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
        /* not sure if needed since we check if closed in running()
        if ( event.type == sf::Event::Closed )
        {
            window.close ();
        }
        */
        current_state->handle_input(event);
    }
}

void State_machine::quit()
{
    // what more?
    window.close();
}
