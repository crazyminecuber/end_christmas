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
#include "Health.h"

class Game final
{
public:
	Game(){};
	Game(sf::Vector2u win_size, std::string const & map_file, int hp
		 /* std::string const & entity_file, */
		 /*std::string const & shop_file,*/
		 )
		 : window_size{win_size.x, win_size.y}, health{window, "resources/textures/heart.png", hp}/*, shop{shop_file}*/
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

	void create_1_enemy_basic();
	void create_1_enemy_boss();
	void create_n_enemy_basic(int start_time, int amount, float interval);
	void create_n_enemy_boss(int start_time, int amount, float interval);
	void enemy_update_direction();
	void enemy_update_position();

	void projectile_update_position();

	void fire_towers();

	int get_frame();
	float get_fps();

	// operator overload
	// std::ostream& operator<<(std::ostream& output, sf::Vector2f const & vector);
	// std::ostream& operator<<(std::ostream& output, sf::Vector2i const & vector);


private:
	sf::Vector2u window_size;
    sf::RenderWindow window{sf::VideoMode{window_size.x, window_size.y},
	 						"Tower defence"};
	//Projectile* get_tower_projectile(std::string const & projectile); ta tillbaka när underklasserna till projectile är gjorda
	bool collided(Entity const *object1, Entity const *object2);
	void init_enemies(nlohmann::json const & json_obj);
	void init_projectiles(nlohmann::json const & json_obj);
	void init_towers(nlohmann::json const & json_obj);
	Health health;
	//Tower_shop tower_shop;
	int frame{0};
	float fps{60};



	Resource_manager resources{};

};
#endif
