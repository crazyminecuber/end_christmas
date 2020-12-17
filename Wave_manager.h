#ifndef WAVE_MANAGER_H
#define WAVE_MANAGER_H

#include <memory> // shared_ptr
#include <vector>
#include <SFML/Graphics.hpp>
#include "Wave_group.h"


class Wave_manager
{
public:
    Wave_manager(std::shared_ptr<sf::RenderWindow> win)
    : window{win}, font{Resource_manager::load_font("resources/fonts/font.ttf")}
    {
        init();
    }

    void init_waves(int current_frame);
    void add_wave(Wave_group* wave_group);
    void next_wave(int current_frame);
    bool wave_is_finished() const;
    int  get_current_wave() const;

    void render()           const;
    bool player_has_won()   const;

    void spawn_enemies(int frame);
    bool all_enemies_have_spawned() const;
    
private:
    int current_wave{1};
    float fps{60};
    int win_wave;

    std::vector<Wave_group*> wave_groups; //All groups defined in entity.json
    std::vector<Wave_group*> active_wave_groups; //The groups that spawn the current wave

    std::shared_ptr<sf::RenderWindow> window;
    sf::Font font;
    sf::RectangleShape background;
    sf::Text text_wave;

    void init();

    void generate_wave(int current_frame);
    void calculate_win_wave();
    void add_active_wave_groups();
    void remove_inactive_wave_groups();
    
    void update_text_waves();    
};


#endif //WAVE_MANAGER.H
