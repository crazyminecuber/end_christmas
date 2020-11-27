#ifndef WAVE_MANAGER_H
#define WAVE_MANAGER_H

#include <list>


class Wave_manager
{
public:
    Wave_manager(){};
    int current_wave{0};

    std::list<int> spawn_frames_basic;
    std::list<int> spawn_frames_boss;

    void next_wave();
    void spawn_enemies(int frame);
    void calculate_spawn_frames(int start_frame, int amount,
                                            int interval, std::list<int> &spawn_frames);
};


#endif //WAVE_MANAGER.H
