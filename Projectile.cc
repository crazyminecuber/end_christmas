#include "Projectile.h"
#include "iostream"
#include "string"
#include "vector"
#include "Game.h"
#include <SFML/Graphics.hpp>

using namespace std;

//Tillhör klass Projectile
vector<Projectile*> Projectile::projectiles;

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
            projectiles.erase(std::remove(projectiles.begin(),
                  projectiles.end(), this), projectiles.end());
            delete &*this;
        }

    }

entity_properties Projectile::prop;
//Tillhör Projectile_basic
//Kopieringskonstruktor som lägger in i lista
Projectile_basic::Projectile_basic(Projectile_basic const& other)
    : Projectile(other)
{
    frame_to_die = Game::get_frame() + frames_to_live;
    projectiles.push_back(& *this);
}

void Projectile_basic::collision()
    {
      projectiles.erase(std::remove(projectiles.begin(),
            projectiles.end(), this), projectiles.end());
      delete &*this;//inte säker på att detta blir rätt. Samma tanke som i update position. Kompilatorn klagar också på att vi inte använder object
    }
entity_properties Projectile_basic::prop;
//Tillhör Projectile_pierce
//Kopieringskonstruktor som lägger in i lista
Projectile_pierce::Projectile_pierce(Projectile_pierce const& other)
    : Projectile(other)
{
    frame_to_die = Game::get_frame() + frames_to_live;
    projectiles.push_back(& *this);
}

void Projectile_pierce::collision()
{
    //delete in Enemy that will delete Enemy
    if(nr_enemies_killed <= nr_pierce)
    {
        nr_enemies_killed+= 1;
    }
    else
    {
      projectiles.erase(std::remove(projectiles.begin(),
            projectiles.end(), this), projectiles.end());
        delete &*this;
    }
}

entity_properties Projectile_pierce::prop;

//Funktion som tillhör Projectile_bomb
//Kopieringskonstruktor som lägger in i lista
Projectile_bomb::Projectile_bomb(Projectile_bomb const& other)
    : Projectile(other)
{
  frame_to_die = Game::get_frame() + frames_to_live;
  projectiles.push_back(& *this);
}

void Projectile_bomb::collision()
{
    //delete in Enemy that will delete Enemy
    //sf::Vector2f pos = this->getPosition();
    new_bomb_blast(this->getPosition());
    // Projectile_bomb_blast* p = new Projectile_bomb_blast{
    //     Projectile_bomb_blast::prop.texture_file, //Texture
    //     pos, //Poistion
    //     Projectile_bomb_blast::prop.size, //Size
    //     Projectile_bomb_blast::prop.hit_rad,        //Hit_rad
    //     Projectile_bomb_blast::prop.dir,       //dir
    //     Projectile_bomb_blast::prop.mov_spd,
    //     Projectile_bomb_blast::arg_damage};          //mov_spd
    // projectiles.push_back(new *p);
    projectiles.erase(std::remove(projectiles.begin(),
          projectiles.end(), this), projectiles.end());
    delete &*this;
  }

void Projectile_bomb::new_bomb_blast(sf::Vector2f position)
{
    Projectile_bomb_blast* p = new Projectile_bomb_blast{
        Projectile_bomb_blast::prop.texture_file, //Texture
        position, //Poistion
        Projectile_bomb_blast::prop.size, //Size
        Projectile_bomb_blast::prop.hit_rad,        //Hit_rad
        Projectile_bomb_blast::prop.dir,       //dir
        Projectile_bomb_blast::prop.mov_spd,
        Projectile_bomb_blast::damage_init};          //mov_spd
    projectiles.push_back(p);
}

entity_properties Projectile_bomb::prop;

// Gör om bomb_blast så att den endast innehåller rad, texture, mm,
//Funktion som tillhör Projectile_bomb_blast
//Kopieringskonstruktor som lägger in i lista
Projectile_bomb_blast::Projectile_bomb_blast(Projectile_bomb_blast const& other)
    : Projectile(other)
{
  frame_to_die = Game::get_frame() + frames_to_live;
  projectiles.push_back(& *this);
}

void Projectile_bomb_blast::collision()
{
    //delete in Enemy that will delete Enemy
    delete &*this;
}

entity_properties Projectile_bomb_blast::prop;
