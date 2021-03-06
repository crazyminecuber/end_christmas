#ifndef STATE_END_H
#define STATE_END_H

#include <SFML/Graphics.hpp>
#include <memory> // shared_ptr
#include "State.h"
#include "Game.h"

class State_end : public State
{
public:
    State_end(std::shared_ptr<sf::RenderWindow> _window,
              std::shared_ptr<Game> _game,
              const sf::Font &_font,
              nlohmann::json &settings_end)
              : State(_window, _game, _font),
                background_texture{Resource_manager::load(
                                       settings_end["background"])}
              {
                  on_resize();
              };

    void handle_input(sf::Event & event) override;
    void update_logic()                  override;
    void render()                        override;

    int get_next_state()                 override;

private:
    void on_resize();
    void update_end_text();

    bool updated{false};
    /* graphics stuff below */
    sf::Texture background_texture;
    sf::Sprite  background_sprite;
    sf::Text    text1;
    sf::Text    text2;
};

#endif // STATE_END_H
