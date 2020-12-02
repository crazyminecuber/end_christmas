#include "Wave_group.h"
#include <list>
#include <algorithm>
#include "Wave_manager.h"
#include "Enemy.h"



void Wave_group::next_wave()
{
}

void Wave_group::calculate_spawn_frames(float fps)
{
    int interval = (1/spawn_rate) * fps;
    //start_frame and interval is in frames
    for(int i = 0; i < amount; i++)
    {
        spawn_frames.push_back(start_frame + interval*i);
    }
}

void Wave_group::spawn_enemies(int frame)
{
    //There might be multiple enemies on one frame
    while(spawn_frames.front() == frame)
    {
        spawn_frames.pop_front();
        Enemy::new_basic();
    }
}
