#include <list>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "Wave_manager.h"
#include "Wave_group.h"
#include "Enemy.h"
#include <iostream> //debug


void Wave_manager::init()
{
    /* text */
    if ( !font->loadFromFile("resources/fonts/font.ttf") )
    {
     std::cout << "Kunde inte ladda font" << std::endl;
    }
    sf::Vector2f text_pos{0,50};
    float text_size{50};
    text_wave.setFont((*font));
    text_wave.setFillColor(sf::Color::White);
    text_wave.setPosition(1, 50);
    text_wave.setCharacterSize(text_size * 0.8);

    update_text_waves();

    /* background */
    sf::Vector2f rect_size{150,50};
    //rect_size.x = (sprite_heart.getGlobalBounds().width +
    //                text_health.getGlobalBounds().width  ) * 1.17;
    //rect_size.y = std::max(sprite_heart.getGlobalBounds().height,
    //                        text_health.getGlobalBounds().height) + 5;
    background.setSize(rect_size);
    background.setFillColor(sf::Color(128, 128, 128));
    background.setOutlineThickness(1);
    background.setPosition(background.getOutlineThickness(),
                           50 + background.getOutlineThickness());
    background.setOutlineColor(sf::Color::Black);
}

void Wave_manager::render()
{
    window.draw(background);
    window.draw(text_wave);
}

void Wave_manager::update_text_waves()
{
    text_wave.setString("Wave:" + std::to_string(current_wave));
}

void Wave_manager::init_waves()
{
}

void Wave_manager::add_wave(Wave_group* wave_group)
{
    wave_groups.push_back(wave_group);
}

void Wave_manager::next_wave(int current_frame, int fps)
{
    ++current_wave;
    update_text_waves();
    for (auto it{begin(wave_groups)}; it != end(wave_groups); ++it)
    {
        (*it)->next_wave(current_wave, current_frame, fps);
    }
}
void Wave_manager::calculate_spawn_frames(float fps)
{
    // std::cout << "spawn_frames calculation begin" << std::endl;
    // for (auto it{begin(wave_groups)}; it != end(wave_groups); ++it)
    // {
        // (*it)->calculate_spawn_frames(current_wave, fps);
    // }
    // std::cout << "spawn_frames calculated" << std::endl;
}

bool Wave_manager::all_enemies_have_spawned()
{
    bool all_have_spawned{true};
    for (auto it{begin(wave_groups)}; it != end(wave_groups); ++it)
    {
        if(!(*it)->all_enemies_have_spawned())
        {
            all_have_spawned = false;
        }
    }
    return all_have_spawned;
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
