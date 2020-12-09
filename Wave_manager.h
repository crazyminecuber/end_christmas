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

    void next_wave(int current_frame, int fps);
    bool wave_is_finished();
    void add_wave(Wave_group* wave_group);
    void render();
    void init_waves(int current_frame, int fps);
    void spawn_enemies(int frame);
    bool all_enemies_have_spawned();
private:
    void init();
    void generate_wave(int current_frame, int fps);

    int current_wave{1};
    std::vector<Wave_group*> wave_groups;
    std::vector<Wave_group*> active_wave_groups; //The groups that spawn the current wave

    sf::RenderWindow & window;
    sf::Font* font;
    sf::RectangleShape background;
    sf::Text text_wave;


    void update_text_waves();
    void add_active_wave_groups();
    void remove_inactive_wave_groups();

    // bool all_enemies_have_spawned();
};


#endif //WAVE_MANAGER.H
