#include <list>
#include "Wave_manager.h"
#include "Wave_group.h"
#include "Enemy.h"

Wave_group::~Wave_group()
{
    enemy->prep_passive_removal();
    delete enemy;
}

int Wave_group::get_start_wave() const
{
    return start_wave;
}

int Wave_group::get_end_wave() const
{
    return end_wave;
}

void Wave_group::next_wave(int current_wave, int current_frame, int fps)
{
    //Update parameters for next wave and calc spawn frames
    if(current_wave != start_wave)
    {
        num_in_group += num_in_group_inc;
        num_of_groups += num_of_groups_inc;
    }

    calculate_spawn_frames(current_frame, fps);
}

void Wave_group::spawn_enemies(int frame)
{
    //There might spawn multiple enemies on one frame
    while(spawn_frames.front() == frame && !spawn_frames.empty())
    // We have to check that's not empty otherwise it will read a random
    // value from Memory and we might get segmentation fault if that's the
    // same as current frame
    {
        spawn_frames.pop_front();
        //Create enemy by cloning the passive enemy
        Enemy::create_enemy_by_obj(enemy->clone());
    }
}

void Wave_group::calculate_spawn_frames(int current_frame,float fps)
{
    //Calculate on which frames the enemies should spawn.
    int start_frame = spawn_delay * fps + current_frame;
    int enemy_interval = (1/spawn_rate) * fps;
    int enemy_group_interval = group_spawn_interval * fps;

    //start_frame and interval is in frames
    for(int g = 0; g < num_of_groups; g++)
    {
        for(int i = 0; i < num_in_group; i++)
        {
            spawn_frames.push_back(start_frame + enemy_interval*i);
        }
        start_frame += enemy_interval * (num_in_group-1) + enemy_group_interval;
    }
}

bool Wave_group::all_enemies_have_spawned() const
{
    return (spawn_frames.empty());
}
