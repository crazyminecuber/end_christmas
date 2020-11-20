#include "Projectile.h"
#include "iostream"
#include "string"
#include "vector"
#include "Game.h"

using namespace std;

vector<Projectile*> Projectile::projectiles;

//Funktioner som tillhör Projectile
// Projectile::Projectile(std::string texture_file, sf::Vector2f position,
//       sf::Vector2f siz, float hit_rad, sf::Vector2f dir, float mov_spd, int arg_damage)
//       {}
//
// Projectile::~Projectile(){}
/*
Projectile::Projectile(Projectile const & other) : Entity::Entity(other)
{
    damage = other.damage;
}
*/

//Next posistion
void Projectile::update_position()
    {
        if (Game::get_frame() < frame_to_die)
        {
            move(direction*movement_speed);
        }
        else
        {
            // kanske returnera något så att game kan ta bort *this ur projectiles och destruera. Annars kommer de finnas pekare i projectiles som pekar på borttagna object väl?
        }
        
    }
/* *****************************************************************************
 * Funktioner som tillhör Projectile_basic */
/**
Projectile_basic::Projectile_basic(std::string texture_file,
        sf::Vector2f position, sf::Vector2f siz,
        float hit_rad, sf::Vector2f dir, float mov_spd)
{

}
*/

//Projectile_basic::~Projectile_basic(){}

//Kopieringskonstruktor som lägger in i lista
Projectile_basic::Projectile_basic(Projectile_basic const& other) 
    : Projectile(other)
{
    frame_to_die = Game::get_frame() + frames_to_live;
    projectiles.push_back(& *this);
}

void Projectile_basic::collision(Entity* object)
    {
        delete &*this;//inte säker på att detta blir rätt. Samma tanke som i update position. Kompilatorn klagar också på att vi inte använder object
    };

/* *****************************************************************************
 * Funktion som tillhör Projectile_pierce */
Projectile_pierce::Projectile_pierce(string texture_file,
        sf::Vector2f position, sf::Vector2f siz,
        float hit_rad, sf::Vector2f dir, float mov_spd)
{
    /* konstruera */
}

Projectile_pierce::~Projectile_pierce(){}

//Kopieringskonstruktor som lägger in i lista
Projectile_pierce::Projectile_pierce(Projectile_pierce const& other) 
    : Projectile(other)
{
    // nr_pierce = ?
    frame_to_die = Game::get_frame() + frames_to_live;
    projectiles.push_back(*this);
}

void Projectile_pierce::collision(Entity* object)
    {
    //delete in Enemy that will delete Enemy
    if(nr_enemies_killed <= nr_pierce)
    {
        nr_enemies_killed+= 1;
    }
    else
    {
        delete *this;
    }
    };

//Funktion som tillhör Projectile_bomb
Projectile_bomb::Projectile_bomb(string texture_file,
        sf::Vector2f position, sf::Vector2f siz,
        float hit_rad, sf::Vector2f dir, float mov_spd)
{
if(game.frame == frame_to_die)
    {
    Projectile*->update_position();
    }
    //delete projectile if beyond frame_to_die
    delete &*this;
}

Projectile_bomb::~Projectile_bomb(){}

//Kopieringskonstruktor som lägger in i lista
Projectile_bomb::Projectile_bomb(Projectile_bomb const& other)
{
    *this = other;
    projectiles.add(*this);
    frame_to_die() = game.frame + frames_to_live();
}

void Projectile_bomb::collision(Entity* object)
    {
    //delete in Enemy that will delete Enemy
    projectiles.add<new Projectile_bomb_blast*>;
    delete Projectile_bomb*;
    };

//Funktion som tillhör Projectile_bomb_blast
Projectile_bomb_blast::Projectile_bomb_blast(string texture_file,
        sf::Vector2f position, sf::Vector2f siz,
        float hit_rad, sf::Vector2f dir, float mov_spd)
{
    if(game.frame == frame_to_die)
    {
    Projectile->update_rad();
    }
    //delete projectile if beyond frame_to_die
    delete *this;
}

Projectile_bomb_blast::~Projectile_bomb_blast(string texture_file,
        sf::Vector2f position, sf::Vector2f siz, float hit_rad,
        sf::Vector2f dir, float mov_spd){}

//Kopieringskonstruktor som lägger in i lista
Projectile::Projectile_bomb_blast(Projectile_bomb_blast const& other)
{
    *this = other;
    projectiles.add(*this);
    frame_to_die() = game.frame + frames_to_live();
}

void Projectile::update_rad(Entity* object)
{
    Projectile.hit_rad += blast_rad;
};

void Projectile::collision(Entity* object)
{
    //delete in Enemy that will delete Enemy
    delete *this;
};
