#include <list>
#include <algorithm>
#include "Wave_manager.h"
#include "Enemy.h"



void Wave_manager::next_wave()
{
    calculate_spawn_frames(120, 10, 60, spawn_frames_basic);
    calculate_spawn_frames(150, 10, 60, spawn_frames_boss);
    spawn_frames_basic.sort();
    spawn_frames_boss.sort();
}

void Wave_manager::calculate_spawn_frames(int start_frame, int amount,
                                        int interval, std::list<int> &spawn_frames)
{
    //start_frame and interval is in frames
    for(int i = 0; i < amount; i++)
    {
        spawn_frames.push_back(start_frame + interval*i);
    }
}

void Wave_manager::spawn_enemies(int frame)
{
    //There might be multiple enemies on one frame
    while(spawn_frames_basic.front() == frame)
    {
        spawn_frames_basic.pop_front();
        Enemy::new_basic();
    }
    while(spawn_frames_boss.front() == frame)
    {
        spawn_frames_boss.pop_front();
        Enemy::new_boss();
    }
}
