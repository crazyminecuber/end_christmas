#ifndef GAME_H
#define GAME_H
#include <string>
#include <vector>
#include "Tower_shop.h"
#include "Resource_manager.h"
#include "Entity.h"
#include "Projectile.h"
#include "json.hpp"
#include "Projectile.h"

class Game final
{
public:
	Game(){};
	Game(std::string const & map_file,
		 /* std::string const & entity_file, */
		 /*std::string const & shop_file,*/
		 int health
		 ) : health{health}/*, shop{shop_file}*/
		 {
			load_map(map_file);
			//load_entities(entity_file);
		 };
	void load_map(std::string const & file);
	void determine_tile_directions();
	bool is_tile_enemy(sf::Vector2i index);
	bool is_tile_enemy_start(sf::Vector2i index);
	bool is_tile_enemy_end(sf::Vector2i index);



	void load_entities(std::string const & file);
	void handle_events();
	void handle_click();
	void update_logic();
	void tile_enemy_set_direction();
	void enemy_update_direction();
	void enemy_update_position();
	void projectile_update_position();
	void check_collision();
	void render();
	void create_enemies();
	void fire_towers();
	void set_window_size(int const width,int const height);
	static int get_frame();

private:
	//Projectile* get_tower_projectile(std::string const & projectile); ta tillbaka när underklasserna till projectile är gjorda
	bool collided(Entity const *object1, Entity const *object2);
	void init_enemies(nlohmann::json const & json_obj);
	void init_projectiles(nlohmann::json const & json_obj);
	void init_towers(nlohmann::json const & json_obj);
	int health;
	//Tower_shop tower_shop;
	unsigned int window_width{1400};
	unsigned int window_height{800};
    sf::RenderWindow window{sf::VideoMode{window_width, window_height}, "Tower defence"};


	Resource_manager resources{};

};
#endif
