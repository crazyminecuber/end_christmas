#include 

class Resource_manager{
    staticmap<string, sf::Texture> resources;
    public:
    static sf::Texture& load(stringconst& file){
        autoit {resources.find(file)};
        if(it == end(resources)){sf::Texture texture;texture.loadFromFile(file);
        it = resources.insert(texture).first;}
        return*(it->second);
    }
}
