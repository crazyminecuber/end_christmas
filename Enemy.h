#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Projectile.h"
#include <string>
#include "json.hpp"

class Enemy
: public Entity
{
public:
    Enemy(std::string texture_file, sf::Vector2f position,
        sf::Vector2f size, float hit_rad,
        sf::Vector2f dir, float mov_spd,
        int arg_life, int reward)
    :Entity(texture_file, position,
            size, hit_rad,
            dir, mov_spd),
            life{arg_life}, kill_reward{reward}
            {}

    virtual Enemy*  clone() const = 0;
    virtual bool    collision(Projectile* object) = 0;

    //Enemy_boss needs to do perfome some
    //actions before it's removed when used
    //as a passive enemy in wave_group.
    virtual void    prep_passive_removal(){}
    
    int get_damage() const;
    int get_reward() const;

    //Statics
    static std::vector<Enemy*> enemies;

    static Enemy*   get_new_enemy(nlohmann::json const & enemies, 
                                std::string chosen_enemy, 
                                sf::Vector2f position_init);
    static void     create_enemy_by_obj(Enemy* enemy);
    static void     delete_all_enemies();

protected:
    int life{};
    int kill_reward{};

private:
    static Enemy* get_new_enemy_basic(nlohmann::json const & enemy_props,
                                    sf::Vector2f position_init);
    static Enemy* get_new_enemy_boss(nlohmann::json const & enemy_props,
                                    sf::Vector2f position_init, 
                                    Enemy* child);
};

#endif //ENEMY_H
