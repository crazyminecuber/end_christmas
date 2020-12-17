#ifndef WAVE_GROUP_H
#define WAVE_GROUP_H

#include <list>
#include "Enemy.h"


class Wave_group
{
public:
    Wave_group(){};

    Wave_group(int start_wave, int end_wave, 
                Enemy* enemy, float spawn_delay, 
                float spawn_rate, int num_in_group, 
                int num_in_group_inc, float group_spawn_interval, 
                int num_of_groups, int num_of_groups_inc)
               :start_wave{start_wave}, 
                end_wave{end_wave}, 
                enemy{enemy}, 
                spawn_delay{spawn_delay}, 
                spawn_rate{spawn_rate}, 
                num_in_group{num_in_group}, 
                num_in_group_inc{num_in_group_inc}, 
                group_spawn_interval{group_spawn_interval}, 
                num_of_groups{num_of_groups},
                num_of_groups_inc{num_of_groups_inc}
                {}

    ~Wave_group();

    int  get_start_wave() const;
    int  get_end_wave()   const;
    void next_wave(int current_wave, int current_frame, int fps);
    
    void calculate_spawn_frames(int current_frame, float fps);
    void spawn_enemies(int frame);
    bool all_enemies_have_spawned() const;
private:
     std::list<int> spawn_frames; //Frames on which enemy should spawn

    int start_wave;
    int end_wave;

    Enemy* enemy;
    float spawn_delay; //sec
    float spawn_rate; //Hz
    int   num_in_group;
    int   num_in_group_inc;

    float group_spawn_interval; //sec
    int   num_of_groups;
    int   num_of_groups_inc;
};


#endif //WAVE_GROUP.H
