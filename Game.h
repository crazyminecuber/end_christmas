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
#include "Projectile.h"
#include "Health.h"
#include "Wave_manager.h"

class Game final
{
public:
	//Game(){};
	Game(sf::Vector2u win_size, std::string const & map_file, int hp
		 /* std::string const & entity_file, */
		 /*std::string const & shop_file,*/
		 )
		 : window_size{win_size.x, win_size.y},
		 health{window, "resources/textures/heart.png", hp},
		 wave_manager{window}/*, shop{shop_file}*/
		 {
			load_map(map_file);
			//load_entities(entity_file);
		 };


	void handle_input();
	void update_logic();
	void render();

	void load_map(std::string const & file);
	void determine_tile_directions();

	bool is_running(); // remove when we make StateMachine
	void check_collision();
	void load_entities(std::string const & file);
	void handle_click(sf::Vector2f click);

	void enemy_update_direction();
	void enemy_update_position();
	void next_wave();

	void projectile_update_position();

	void fire_towers();

	int get_frame();
	float get_fps();

private:
	sf::Vector2u window_size;
    sf::RenderWindow window{sf::VideoMode{window_size.x, window_size.y},
	 						"Tower defence"};
	//Projectile* get_tower_projectile(std::string const & projectile); ta tillbaka när underklasserna till projectile är gjorda
	bool collided(Entity const *object1, Entity const *object2);
	void init_enemies(nlohmann::json const & json_obj);
	void init_waves(nlohmann::json const & json_obj);
	void init_projectiles(nlohmann::json const & json_obj);
	void init_towers(nlohmann::json const & json_obj);
	Health health;
	Wave_manager wave_manager;

	//Tower_shop tower_shop;
	int frame{0};
	float fps{60}; //Change to int???



	Resource_manager resources{};

};

// operator overload for sf::Vector2
std::ostream& operator<<(std::ostream& output, sf::Vector2f const & vector);
std::ostream& operator<<(std::ostream& output, sf::Vector2i const & vector);
std::ostream& operator<<(std::ostream& output, sf::Vector2u const & vector);

#endif
