#include "Wave_group.h"
#include <list>
#include <algorithm>
#include "Wave_manager.h"
#include "Enemy.h"
#include <iostream>



void Wave_group::next_wave()
{
}

void Wave_group::calculate_spawn_frames(float fps)
{
    int enemy_interval = (1/spawn_rate) * fps;
    int enemy_group_interval = group_spawn_interval * fps;
    //start_frame and interval is in frames
    for(int g = 0; g < num_of_groups; g++)
    {
        for(int i = 0; i < num_in_group; i++)
        {
            spawn_frames.push_back(start_frame +
                                    enemy_interval*i +
                                    enemy_group_interval*g);
        }
    }
}

void Wave_group::spawn_enemies(int frame)
{

    //There might be multiple enemies on one frame
    while(spawn_frames.front() == frame && !spawn_frames.empty())
    //We have to check that's not empty otherwise it will read a random
    // value from Memory and we might get segmentation fault if that's the
    // same as current frame
    {
        spawn_frames.pop_front();
        Enemy::new_basic();
    }
}
