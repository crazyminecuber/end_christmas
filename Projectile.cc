#include "Projectile.h"
#include "iostream"
#include "string"
#include "vector"
#include "Game.h"

using namespace std;

vector<Projectile*> Projectile::projectiles;

// Projectile::Projectile(Projectile const& other) : Entity(other)
// {
//
// }

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
            delete this;
        }

    }

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
      delete this;//inte säker på att detta blir rätt. Samma tanke som i update position. Kompilatorn klagar också på att vi inte använder object
    }


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
        delete this;
    }
}

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
    projectiles.erase(std::remove(projectiles.begin(),
          projectiles.end(), this), projectiles.end());
    delete this;
    projectiles.push_back(new *Projectile_bomb_blast);
}
// Gör om bomb_blast så att den endast innehåller rad, texture, mm, 
//Funktion som tillhör Projectile_bomb_blast
//Kopieringskonstruktor som lägger in i lista
Projectile::Projectile_bomb_blast(Projectile_bomb_blast const& other)
    : Projectile(other)
{
  frame_to_die = Game::get_frame() + frames_to_live;
  projectiles.push_back(& *this);
}

void Projectile::collision()
{
    //delete in Enemy that will delete Enemy
    delete this;
};
