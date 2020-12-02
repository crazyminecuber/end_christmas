#ifndef WAVE_GROUP_H
#define WAVE_GROUP_H

#include <list>


class Wave_group
{
public:
    Wave_group(){};

    Wave_group(int start_frame, int amount, float mov_spd_factor,
               float spawn_rate, int num_of_groups, float group_interval)
    : start_frame{start_frame}, amount{amount}, mov_spd_factor{mov_spd_factor},
      spawn_rate{spawn_rate}, num_of_groups{num_of_groups}, group_interval{group_interval}
    {
        //init();
    }

    std::list<int> spawn_frames;

    void next_wave();
    void spawn_enemies(int frame);
    void calculate_spawn_frames(float fps);
private:
    //Enemy* enemy;
    //int current_wave;
    int start_frame;
    int amount;
    float mov_spd_factor;
    float spawn_rate; //(Hz)
    int num_of_groups;
    float group_interval; //(i sekunder)
};


#endif //WAVE_MANAGER.H
