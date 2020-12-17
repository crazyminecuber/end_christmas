#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>

class Resource_manager{
    public:
      static int get_num_of_resources()
      {
        return resources.size();
      }
    static sf::Texture& load(std::string const& file){
        auto it{resources.find(file)};
        if(it == end(resources)){
          sf::Texture texture{};
          if ( texture.loadFromFile(file) )
          {
            resources.insert({file, texture});
          }
          else 
          {
            std::cout << "Error: Could not load " + file << std::endl;
          }
        }
        return resources[file];
    }
    static sf::Font& load_font(std::string const& file){
        auto it{fonts.find(file)};
        if(it == end(fonts)){
          sf::Font font{};
          if ( font.loadFromFile(file) )
          {
            fonts.insert({file, font});
          }
          else 
          {
            std::cout << "Error: Could not load " + file << std::endl;
          }
        }
        return fonts[file];
    }
  private:
    static std::map<std::string, sf::Texture> resources;
    static std::map<std::string, sf::Font> fonts;

};

#endif // RESOURCE_MANAGER_H
