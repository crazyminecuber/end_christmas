#include "State_pause.h"
#include <memory> // shared_ptr
#include <string>
using namespace std;

State_pause::State_pause(std::shared_ptr<sf::RenderWindow> _window,
    std::shared_ptr<Game> _game, 
    const sf::Font & _font)
: State(_window, _game, _font)
{
    init();
}

void State_pause::init()
{
    /* text */
    string file{"resources/fonts/Christmas_Bell.otf"};
    if (!font.loadFromFile(file))
    {
        throw invalid_argument("Unable to load " + file);
    }

    string str = "Pause";
    text_pause = sf::Text{'('+str+')', font, 100};
    sf::FloatRect bb_pause{text_pause.getGlobalBounds()};
    text_pause.setOrigin(bb_pause.width / 2.f, bb_pause.height / 2.f);

    on_resize();
}

void State_pause::handle_input(sf::Event & event)
{
    if ( event.type == sf::Event::KeyPressed )
    {
        if ( event.key.code == sf::Keyboard::Escape )
        {
            unpause_game = true;
        }
    }

    if ( event.type == sf::Event::Resized )
    {
        on_resize();
    }
}

void State_pause::update_logic()
{
    ;
}

void State_pause::render()
{
    window->clear();

    /* put stuff to render here */
    game->render();
    window->draw(shader);
    window->draw(text_pause);
    /*                          */

    window->display();
}

int State_pause::get_next_state()
{
    int return_value{PAUSE};
    if ( unpause_game )
    {
        return_value = WAVE;
    }
    /* reset variables */
    unpause_game = false;

    return return_value;
}

void State_pause::on_resize()
{
    /* shader */
    sf::Vector2f window_size(window->getSize().x,
                             window->getSize().y);
    shader.setSize(window_size);
    shader.setFillColor(sf::Color(0, 0, 0, 140));
    shader.setPosition(0, 0);

    text_pause.setPosition(window_size.x / 2.f, window_size.y / 2.f);
}
