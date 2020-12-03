#include <list>
#include <algorithm>
#include "Wave_manager.h"
#include "Wave_group.h"
#include "Enemy.h"
#include <iostream>


void Wave_manager::init_waves()
{
    std::cout << "Init waves" << std::endl;
    // wave_groups.push_back(new Wave_group(0, 20, 1, 5, 2, 0.1));
    // wave_groups.push_back(new Wave_group(300, 20, 1, 1, 2, 0.1));
}

void Wave_manager::add_wave(int start_wave, int end_wave, int start_frame,
                            float mov_spd_factor, float spawn_rate, int num_in_group,
                            int num_of_groups, float group_spawn_interval)
{
    wave_groups.push_back(new Wave_group(start_wave, end_wave, start_frame,
               mov_spd_factor, spawn_rate, num_in_group,
               num_of_groups, group_spawn_interval));
    std::cout << "Waved pushed" << std::endl;
}

void Wave_manager::next_wave()
{
    //calculate_spawn_frames(120, 10, 60, spawn_frames_basic);
    //calculate_spawn_frames(150, 10, 60, spawn_frames_boss);
    //spawn_frames_basic.sort();
    //spawn_frames_boss.sort();
}
void Wave_manager::calculate_spawn_frames(float fps)
{
    std::cout << "spawn_frames calculation begin" << std::endl;
    for (auto it{begin(wave_groups)}; it != end(wave_groups); ++it)
    {
        (*it)->calculate_spawn_frames(fps);
    }
    std::cout << "spawn_frames calculated" << std::endl;
}



// void Wave_manager::calculate_spawn_frames(int start_frame, int amount,
                                        // int interval, std::list<int> &spawn_frames)
// {
    //start_frame and interval is in frames
    // for(int i = 0; i < amount; i++)
    // {
        // spawn_frames.push_back(start_frame + interval*i);
    // }
// }

void Wave_manager::spawn_enemies(int frame)
{
    //There might be multiple enemies on one frame
    // while(spawn_frames_basic.front() == frame)
    // {
    //     spawn_frames_basic.pop_front();
    //     Enemy::new_basic();
    // }
    // while(spawn_frames_boss.front() == frame)
    // {
    //     spawn_frames_boss.pop_front();
    //     Enemy::new_boss();
    // }
    //std::cout << "enemies spawn begin" << std::endl;
    for (auto it{begin(wave_groups)}; it != end(wave_groups); ++it)
    {
        if((*it)->spawn_frames.size()>0)
        {
            (*it)->spawn_enemies(frame);
        }

    }
    // /std::cout << "enemies spawned" << std::endl;
}
