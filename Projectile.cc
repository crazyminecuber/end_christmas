#include "Projectile.h"
#include <iostream>
#include <string>
#include <vector>
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
//clone and add direction
Projectile*  Projectile_basic::clone(sf::Vector2f direction)
{
  Projectile_basic* p = new Projectile_basic{
      Projectile_basic::prop.texture_file,  //Texture
      position,                            //Poistion
      Projectile_basic::prop.size,        //Size
      Projectile_basic::prop.hit_rad,    //Hit_rad
      Projectile_basic::prop.dir,       //dir
      Projectile_basic::prop.mov_spd,  //mov_spd
      Projectile_basic::damage_init};
  projectiles.push_back(p);
}
//Removes and delete the porjectile when collided with an enemy
void Projectile_basic::collision()
    {
      projectiles.erase(std::remove(projectiles.begin(),
            projectiles.end(), this), projectiles.end());
      delete &*this;
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
//clone and add direction
Projectile*  Projectile_pierce::clone(sf::Vector2f direction)
{
  Projectile_pierce* p = new Projectile_pierce{
      Projectile_pierce::prop.texture_file, //Texture
      position, //Poistion
      Projectile_pierce::prop.size, //Size
      Projectile_pierce::prop.hit_rad,        //Hit_rad
      Projectile_pierce::prop.dir,       //dir
      Projectile_pierce::prop.mov_spd,
      Projectile_pierce::damage_init};
  projectiles.push_back(p);
}
//Counts nr of enemies killed and remove and delete the projectile when
// nr_pierce nr of enemies is killed
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
//clone and add direction
Projectile*  Projectile_bomb::clone(sf::Vector2f direction)
{
  Projectile_bomb* p = new Projectile_bomb{
      Projectile_bomb::prop.texture_file, //Texture
      position, //Poistion
      Projectile_bomb::prop.size, //Size
      Projectile_bomb::prop.hit_rad,        //Hit_rad
      Projectile_bomb::prop.dir,       //dir
      Projectile_bomb::prop.mov_spd,
      Projectile_bomb::damage_init};
  projectiles.push_back(p);
}

//adds bomb_blast to projectiles vector and remove and delete the projectile
void Projectile_bomb::collision()
{
    //delete in Enemy that will delete Enemy
    //sf::Vector2f pos = this->getPosition();
    new_bomb_blast(this->getPosition());
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
//remove and delete the projectile when collided with enemies
void Projectile_bomb_blast::collision()
{
    //delete in Enemy that will delete Enemy
    delete &*this;
}

entity_properties Projectile_bomb_blast::prop;
