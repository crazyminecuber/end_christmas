#ifndef ENEMY_H
#define ENEMY_H

//TODO Ska vi ha någon funktion för att manipulera vektorn med enemies?
//TODO Behöver vi en funktion för att skapa fiender?
//TODO Göra en struct för alla entity properties
//TODO Använda överlagring när vi skapar fiender för att kunna skapa med och utan special inställningar.
#include <vector>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Projectile.h"

class Enemy
: public Entity
{
public:
    Enemy(std::string texture_file, sf::Vector2f position,
        sf::Vector2f size, float hit_rad,
        sf::Vector2f dir, float mov_spd,
        int arg_life)
    :Entity(texture_file, position,
        size, hit_rad,
        dir, mov_spd),
        life{arg_life}{}

    virtual bool collision(Projectile* object) = 0;
    void set_direction(sf::Vector2f dir);
    virtual Enemy* clone() = 0;
    int get_damage();

    //Statics
    static Enemy* get_new_enemy_basic();
    static Enemy* get_new_enemy_boss();
    static void create_enemy_by_obj(Enemy* enemy);
    static void new_basic();
    static void new_basic(sf::Vector2f position);
    static void new_boss();

    static void delete_all_enemies();
    static std::vector<Enemy*> enemies;
    static sf::Vector2f position_init; //Enemies should start at same positions

    protected:
        int life;
};


#endif //ENEMY_H
