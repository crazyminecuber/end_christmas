#ifndef WAVE_MANAGER_H
#define WAVE_MANAGER_H

#include <list>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Wave_group.h"


class Wave_manager
{
public:
    Wave_manager(sf::RenderWindow & win)
    : window{win}, font{new sf::Font}
    {
        init();
    }

    int current_wave{0};


    sf::RenderWindow & window;
    sf::Font* font;
    sf::RectangleShape background;
    sf::Text text_wave;

    std::vector<Wave_group*> wave_groups;
    std::vector<Wave_group*> active_wave_groups; //The groups that spawn the current wave

    void init();
    void update_text_waves();
    void add_wave(Wave_group* wave_group);
    void activate_wave_groups();
    void deactive_wave_groups();
    void init_waves();
    void next_wave(int current_frame, int fps);
    void spawn_enemies(int frame);
    bool all_enemies_have_spawned();
    void calculate_spawn_frames(float fps);
    void render();
};


#endif //WAVE_MANAGER.H
