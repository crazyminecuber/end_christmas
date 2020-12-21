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

    static sf::Font& get_standard_font()
    {
      return load_font(standard_font);
    }

    static void set_standard_font(std::string file)
    {
      standard_font = file;
    }

  private:
    static std::map<std::string, sf::Texture> resources;
    static std::map<std::string, sf::Font> fonts;
    static std::string standard_font;

};

#endif // RESOURCE_MANAGER_H
