#include "State_wait.h"
#include "Tower.h"
#include <memory> // shared_ptr
using namespace std;

State_wait::State_wait(std::shared_ptr<sf::RenderWindow> _window, 
        std::shared_ptr<Game> _game,
        const sf::Font &_font)
    : State(_window, _game, _font)
{
    text_wait = sf::Text{"(Press P To Start Next Wave)", font, 60};

    sf::FloatRect bb_wait{text_wait.getGlobalBounds()};
    text_wait.setOrigin(bb_wait.width  / 2.f, bb_wait.height / 2.f);
    text_wait.setPosition(
        window->getSize().x * 0.5f,
        window->getSize().y *0.01f);
}
void State_wait::handle_input(sf::Event & event)
{
    game->handle_input(event);
    if ( event.type == sf::Event::KeyPressed )
    {
        if ( event.key.code == sf::Keyboard::P )
        {
            play = true;
        }
    }
}

void State_wait::update_logic()
{
    game->projectile_update_position();
    //game->update_frame();
}

void State_wait::render()
{
    window->clear();

    game->render();

    window->draw(text_wait);

    window->display();
}

int State_wait::get_next_state()
{
    int return_value{WAIT};
    if (play)
    {
        Projectile::projectiles.clear();
        return_value = WAVE;
        game->next_wave();
    }
    play = false;
    return return_value;
}
