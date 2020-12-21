#include "State_wait.h"
#include "Tower.h"
#include <memory> // shared_ptr

using namespace std;

void State_wait::handle_input(sf::Event & event)
/* handles both general game input and specific state input */
{
    // game input
    game->handle_input(event);

    // state input
    if ( event.type == sf::Event::KeyPressed )
    {
        if ( event.key.code == sf::Keyboard::P )
        {
            // start next wave
            play = true;
        }
        else if ( event.key.code == sf::Keyboard::R )
        {
            // toggle showing tower_radii
            game->set_render_tower_radii(
                                         !(game->get_render_tower_radii())
                                        );
        }
    }

    if ( event.type == sf::Event::Resized )
    {
        on_resize();
    }
}

void State_wait::update_logic()
{
    game->projectile_update_position();
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
    int next_state{WAIT};
    if ( play )
    {
        // clear all projectiles before next wave starts
        for (Projectile *p : Projectile::projectiles)
        {
            delete p;
        }
        Projectile::projectiles.clear();
        next_state = WAVE;
        game->next_wave();
    }

    /* reset variables */
    play = false;
    return next_state;
}

void State_wait::on_resize()
{
    text_wait = sf::Text{"(Press P To Start Next Wave)", font, 45};
    sf::FloatRect bb_wait{text_wait.getGlobalBounds()};
    text_wait.setOrigin(bb_wait.width  / 2.f, bb_wait.height / 2.f);
    text_wait.setPosition(window->getSize().x * 0.5f,
                          window->getSize().y *0.01f);
    text_wait.setFillColor(sf::Color::Black);
}
