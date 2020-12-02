#include <list>
#include <algorithm>
#include "Wave_manager.h"
#include "Wave_group.h"
#include "Enemy.h"


void Wave_manager::init_waves()
{
    wave_groups.push_back(new Wave_group(0, 20, 1, 5, 2, 1));
    wave_groups.push_back(new Wave_group(300, 20, 1, 1, 2, 1));
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
    for (auto it{begin(wave_groups)}; it != end(wave_groups); ++it)
    {
        (*it)->calculate_spawn_frames(fps);
    }
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
    for (auto it{begin(wave_groups)}; it != end(wave_groups); ++it)
    {
        (*it)->spawn_enemies(frame);
    }

}
