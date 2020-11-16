#include <vector>
#include "Entity.h"

class Enemy : public Entity
{
    public:
        Enemy(std::string texture_file, sf::Vector2f position,
              sf::Vector2f siz, float hit_rad,
              sf::Vector2f dir, float mov_spd,
              int arg_life):
              Entity(std::string texture_file,
              sf::Vector2f position, sf::Vector2f siz,
              float hit_rad, sf::Vector2f dir, float mov_spd),
              life{arg_life}{}

        ~Enemy();
        static std::vector<Enemy*> enemies;
    private:
        int life;
};
