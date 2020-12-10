#ifndef GAME_H
#define GAME_H
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "Tower_shop.h"
#include "Resource_manager.h"
#include "Entity.h"
#include "Projectile.h"
#include "json.hpp"
#include "Health.h"
#include "Wave_manager.h"

class Game final
{
public:
	//Game(){};
	Game(sf::RenderWindow & win, std::string const & file_entity, int hp
		 /*std::string const & shop_file,*/
		 )
		 : window{win}, window_size{win.getSize()},
		   health{win, "resources/textures/heart.png", hp},
		   wave_manager{win}/*, shop{shop_file}*/
		 {
			// OBS! This is now done in State_menu::get_next_state() because
			// we need to wait for the user to select a map before
			// loading map. And we need to load map before loading entities

			// load_map(file_entity);
			// load_entities(file_entity);
		 };


	void handle_input(sf::Event & event);
	void update_logic();
	void render();

	void load_map(std::string const & file_entity);
	void determine_tile_directions();

	void load_entities(std::string const & file_entity);
	bool is_running(); // remove when we make StateMachine
	void check_collision();
	void check_collision_towers();
	void handle_click(sf::Vector2f click);

	void enemy_update_direction();
	void enemy_update_position();
	bool wave_complete();
	void next_wave();
	int get_current_wave() const;

	void projectile_update_position();

	void fire_towers();

	static int get_frame();
	int get_health();
	double get_fps(); // ta bort

	void set_selected_map(std::string map_name);

	void init_tiles(std::string const & file_entity);
	std::map<std::string, std::map<std::string, std::string>> maps;

private:
	sf::RenderWindow & window;
	sf::Vector2u window_size;
    //sf::RenderWindow window{sf::VideoMode{window_size.x, window_size.y},
	// 						"Tower defence"};
	Projectile* get_tower_projectile(std::string const & projectile);
	bool collided(Entity const *object1, Entity const *object2);
	void init_enemies(nlohmann::json const & json_obj);
	void init_waves(nlohmann::json const & json_obj);
	void init_projectiles(nlohmann::json const & json_obj);
	void init_towers(nlohmann::json const & json_obj);
	void init_shop(nlohmann::json const & json_obj);
	Health health;
	static int frame;
	double fps{60}; // ta bort
	Wave_manager wave_manager;


    Tower_shop shop;
    Wallet wallet;

	Resource_manager resources{};

	std::map<std::string, std::map<std::string, std::string> > map_tiles;
	std::string selected_map;
};

// operator overload for sf::Vector2
std::ostream& operator<<(std::ostream& output, sf::Vector2f const & vector);
std::ostream& operator<<(std::ostream& output, sf::Vector2i const & vector);
std::ostream& operator<<(std::ostream& output, sf::Vector2u const & vector);

#endif
