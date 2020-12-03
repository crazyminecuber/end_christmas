#ifndef WAVE_GROUP_H
#define WAVE_GROUP_H

#include <list>


class Wave_group
{
public:
    Wave_group(){};

    Wave_group(int start_wave, int end_wave, int start_frame,
               float mov_spd_factor, float spawn_rate, int num_in_group_inc,
               int num_in_group, int num_of_groups, float group_spawn_interval)
    : start_wave{start_wave}, end_wave{end_wave}, start_frame{start_frame},
      mov_spd_factor{mov_spd_factor}, spawn_rate{spawn_rate}, num_in_group_inc{num_in_group_inc},
      num_in_group{num_in_group}, num_of_groups{num_of_groups},
      group_spawn_interval{group_spawn_interval}
    {
        //init();
    }

    std::list<int> spawn_frames;

    void next_wave(int current_wave, int current_frame, int fps);
    void spawn_enemies(int frame);
    bool all_enemies_have_spawned();
    void calculate_spawn_frames(float fps);
private:
    //Enemy* enemy;
    //int current_wave;
    int start_wave;
    int end_wave;
    int start_frame;

    float mov_spd_factor;
    //Group of enemies
    float spawn_rate; //(Hz)
    int num_in_group_inc;
    int num_in_group;
    int num_of_groups;
    float group_spawn_interval; //(sec)

};


#endif //WAVE_MANAGER.H
