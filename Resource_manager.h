#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class Resource_manager{
    public:
      static int get_num_of_resources()
      {
        return std::size(resources);
      }
    static sf::Texture& load(std::string const& file){
        auto it{resources.find(file)};
        if(it == end(resources)){
          sf::Texture texture{};
          texture.loadFromFile(file);
          resources.insert({file, texture});
        }
        return resources[file];
    }
  private:
    static std::map<std::string, sf::Texture> resources;

};

#endif // RESOURCE_MANAGER_H
