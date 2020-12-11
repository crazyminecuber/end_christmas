#include <list>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <iostream> //debug
#include "Wave_manager.h"
#include "Wave_group.h"
#include "Enemy.h"


//Public

void Wave_manager::init_waves(int current_frame, int fps)
{
    generate_wave(current_frame, fps);
    calculate_win_wave();
    std::cout << win_wave << std::endl;
}

void Wave_manager::next_wave(int current_frame, int fps)
{

    ++current_wave;
    std::cout << "next wave: " << current_wave << std::endl;
    update_text_waves();
    generate_wave(current_frame, fps);
}

bool Wave_manager::wave_is_finished()
{
    return (Enemy::enemies.size() == 0 && all_enemies_have_spawned());
}

bool Wave_manager::player_has_won()
{
    return (current_wave == win_wave);
}

void Wave_manager::render()
{
    window.draw(background);
    window.draw(text_wave);
}

//Private
void Wave_manager::init()
{
    /* text */
    if ( !font->loadFromFile("resources/fonts/font.ttf") )
    {
     std::cout << "Kunde inte ladda font för wave_manager" << std::endl;
    }
    sf::Vector2f text_pos{0,50};
    float text_size{50};
    text_wave.setFont((*font));
    text_wave.setFillColor(sf::Color::White);
    text_wave.setPosition(1, 50);
    text_wave.setCharacterSize(text_size * 0.8);

    update_text_waves();

    sf::Vector2f rect_size{150,50};
    background.setSize(rect_size);
    background.setFillColor(sf::Color(128, 128, 128));
    background.setOutlineThickness(1);
    background.setPosition(background.getOutlineThickness(),
                           50 + background.getOutlineThickness());
    background.setOutlineColor(sf::Color::Black);
}

void Wave_manager::generate_wave(int current_frame, int fps)
{
    std::cout << "generate wave" << std::endl;
    add_active_wave_groups();
    remove_inactive_wave_groups();
    for (auto it{begin(active_wave_groups)}; it != end(active_wave_groups); ++it)
    {
        (*it)->next_wave(current_wave, current_frame, fps);
    }
}

void Wave_manager::calculate_win_wave()
{
    int last_wave{0};
    for (auto it{begin(wave_groups)}; it != end(wave_groups); ++it)
    {
        if((*it)->get_end_wave() > last_wave)
        {
            last_wave = (*it)->get_end_wave();
        }
    }
    win_wave = last_wave + 1;
}

void Wave_manager::add_wave(Wave_group* wave_group)
{
    wave_groups.push_back(wave_group);
}

void Wave_manager::update_text_waves()
{
    text_wave.setString("Wave:" + std::to_string(current_wave));
}

void Wave_manager::add_active_wave_groups()
{
    for (auto it{begin(wave_groups)}; it != end(wave_groups); ++it)
    {
        if(current_wave == (*it)->get_start_wave())
        {
            std::cout << "Add wave: " << (*it)->get_start_wave() << std::endl;
            active_wave_groups.push_back((*it));
        }
    }
}

void Wave_manager::remove_inactive_wave_groups()
{
    for (auto it{begin(active_wave_groups)}; it != end(active_wave_groups); ++it)
    {
        if(current_wave == (*it)->get_end_wave() + 1)
        {
            std::cout << "Erase wave" << std::endl;
            active_wave_groups.erase(it);
        }
    }
}

void Wave_manager::spawn_enemies(int frame)
{
    for (auto it{begin(active_wave_groups)}; it != end(active_wave_groups); ++it)
    {
        if((*it)->spawn_frames.size()>0)
        {
            (*it)->spawn_enemies(frame);
        }

    }
}

bool Wave_manager::all_enemies_have_spawned()
{
    bool all_have_spawned{true};
    for (auto it{begin(active_wave_groups)}; it != end(active_wave_groups); ++it)
    {
        if(!(*it)->all_enemies_have_spawned())
        {
            all_have_spawned = false;
        }
    }
    return all_have_spawned;
}

int Wave_manager::get_current_wave() const
{
    return current_wave;
}
