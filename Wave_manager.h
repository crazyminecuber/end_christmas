#ifndef WAVE_MANAGER_H
#define WAVE_MANAGER_H

#include <list>
#include <vector>
#include "Wave_group.h"


class Wave_manager
{
public:
    Wave_manager(){};
    int current_wave{0};

    //
    // spawn_rate (i sekunder)
    // mov_spd_factor
    // num_of_groups
    // group_interval (i sekunder)

    //std::list<int> spawn_frames_basic;
    //std::list<int> spawn_frames_boss;
    std::vector<Wave_group*> wave_groups;
    std::vector<Wave_group*> active_wave_groups; //The groups that spawn the current wave
    void add_wave(int start_wave, int end_wave, int start_frame,
               float mov_spd_factor, float spawn_rate, int num_in_group,
               int num_of_groups, float group_spawn_interval);
    void activate_wave_groups();
    void deactive_wave_groups();
    void init_waves();
    void next_wave();
    void spawn_enemies(int frame);
    void calculate_spawn_frames(float fps);
};


#endif //WAVE_MANAGER.H
