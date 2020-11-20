#ifndef GAME_H
#define GAME_H
#include <string>
#include <vector>
#include "tower_shop.h"
#include "Resource_manager.h"
#include "Entity.h"
#include "json.hpp"

class Game final
{
	public:
	Game(){};
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
	void set_window_size(int const width,int const height);

	private:
	void init_enemies(nlohmann::json const & json_obj);
	void init_projectiles(nlohmann::json const & json_obj);
	void init_towers(nlohmann::json const & json_obj);
	int health;
	Tower_shop tower_shop;
	int current_frame{};
	int window_width{};
	int window_height{};
	Resource_manager resources{};
	
};
#endif