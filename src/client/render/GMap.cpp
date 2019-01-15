#include "GMap.h"
#include "TextureManager.h"
#include "state/Tileset.h"
#include <sys/time.h> 
#include <iostream> 

namespace render {

  GMap::GMap(std::shared_ptr<state::Map> map):
    map(map)
  {
    
  }

  void GMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    
    struct timeval tp;
    gettimeofday(&tp, NULL);
    int time = (tp.tv_sec * 1000 + tp.tv_usec / 1000) % 86400000;
    
    
    state::Tileset tileset= map->getTileset();

    for(unsigned int x = 0; x < map->getSize().x; x++){
      for(unsigned int y = 0; y < map->getSize().y; y++){
        
        sf::IntRect rectangle = tileset.getTileIntRect(map->getData(sf::Vector2u(x,y)), time + x*44 + y*33);
        // x*44 + y*33 are used to simulate a wind effect on animations
        sf::Sprite sprite(*(TextureManager::getTexture("mapTexture")), rectangle);
        
        sprite.setPosition(x*tileset.getTileSize().x, y*tileset.getTileSize().y);
        target.draw(sprite);
      }
    }

  }
  
    sf::Sprite GMap::getTile(sf::Vector2u coord) {
        if(coord.x >= map->getSize().x || coord.y >= map->getSize().y){
            coord = sf::Vector2u(0, 0);
        }

        struct timeval tp;
        gettimeofday(&tp, NULL);
        int time = (tp.tv_sec * 1000 + tp.tv_usec / 1000) % 86400000;

        state::Tileset tileset= map->getTileset();

        sf::IntRect rectangle = tileset.getTileIntRect(map->getData(coord), time);
        return sf::Sprite(*(TextureManager::getTexture("mapTexture")), rectangle);
    }
    std::string GMap::getTileDescription(sf::Vector2u coord, std::string attribute) {
        if(coord.x >= map->getSize().x || coord.y >= map->getSize().y){
            coord = sf::Vector2u(0, 0);
        }
        auto attributes = map->getTile(coord)->attributes;
        if(attributes.find(attribute) == attributes.end()){
            return "--";
        } else {
            
            return attributes[attribute] == -1 ? "--" : std::to_string(attributes[attribute]);
        }
    }     
};

