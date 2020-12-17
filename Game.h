#ifndef GAME_H
#define GAME_H
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <memory> // shared_ptr
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
	Game() = delete;
	Game(std::shared_ptr<sf::RenderWindow> win,
	 	 std::string const & file_health_font,
		 std::string const & file_health_texture,
		 int hp)
		 /*std::string const & shop_file,*/
		 : window{win},
		   health{win, file_health_font, file_health_texture, hp},
		   wave_manager{win}/*, shop{shop_file}*/
		 {

		 };
	~Game();


	void handle_input(sf::Event & event);
	void update_logic();
	void render();

	void load_map(nlohmann::json const& entity,
				  nlohmann::json const& settings);
	void determine_tile_directions();

	void init_entities(nlohmann::json const& entity);
	void check_collision();
	void check_collision_towers();
	void handle_left_click(sf::Vector2f click);
	void handle_right_click(sf::Vector2f click);

	void enemy_update_direction();
	void enemy_update_position();
	bool wave_complete();
	bool player_has_won();
	void next_wave();
	int get_current_wave() const;

	void projectile_update_position();

	void fire_towers();

	static int get_frame();
	void update_frame();
	int get_health();
	sf::Vector2u get_window_size();

	void set_selected_map(std::string map_name);

	void set_render_tower_radii(bool render);
	bool get_render_tower_radii();

	// void init_tiles(std::string const & file_entity);
	void init_tiles(nlohmann::json const& entity);
	std::map<std::string, std::map<std::string, std::string>> maps;

private:
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<Projectile> get_tower_projectile(std::string const & projectile);
	bool collided(Entity const *object1, Entity const *object2,
		float &sq_distance);
	bool collided_bb(Entity const *object1, Entity const *object2);
	void init_waves(nlohmann::json const & waves, nlohmann::json const & enemies);
	void init_projectiles(nlohmann::json const & json_obj);
	void init_towers(nlohmann::json const & json_obj);
	void init_shop(nlohmann::json const & json_obj);
	Health health;
	static int frame;
	Wave_manager wave_manager;
	bool render_tower_radii{false};


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
