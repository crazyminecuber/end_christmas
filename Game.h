#ifndef GAME_H
#define GAME_H
#include <string>
#include <vector>
/*
#include "Shop.h"
#include "Resource_manager.h"
*/
#include "Entity.h"

class Game final
{
	public:
	Game(std::string const & map_file, 
		 std::string const & entity_file,
		 /*std::string const & shop_file,*/
		 int health
		 ) : health{health}/*, shop{shop_file}*/
		 {
			load_map(map_file);
			load_entities(entity_file);
		 };
	void load_map(std::string const & file);
	void load_entities(std::string const & file);
	void handle_input();
	void update_logic();
	void tile_enemy_set_direction();
	void enemy_update_direction();
	void enemy_update_position();
	void projectile_update_position();
	void check_collision();
	void render_game();
	void create_enemies();
	void fire_towers();

	private:
	int health;
	//Shop shop;
	int current_frame{};
	//Resource_manager resources{};
	
};
#endif