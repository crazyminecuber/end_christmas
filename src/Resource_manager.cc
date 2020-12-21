#include "Resource_manager.h"
#include <map>
#include <SFML/Graphics.hpp>
std::map<std::string, sf::Texture> Resource_manager::resources;
std::map<std::string, sf::Font> Resource_manager::fonts;
std::string Resource_manager::standard_font;
