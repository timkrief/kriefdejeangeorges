#include "GMap.h"
#include "TextureManager.h"
#include "state/Tileset.h"
#include <chrono> 

namespace render {

  GMap::GMap(std::shared_ptr<state::Map> map):
    map(map)
  {
    
  }

  void GMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    
  
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    
    state::Tileset tileset= map->getTileset();

    for(unsigned int x = 0; x < map->getSize().x; x++){
      for(unsigned int y = 0; y < map->getSize().y; y++){
        
        sf::IntRect rectangle = tileset.getTileIntRect(map->getData(sf::Vector2u(x,y)), time);
        sf::Sprite sprite(*(TextureManager::getTexture("mapTexture")), rectangle);
        
        sprite.setPosition(x*tileset.getTileSize().x, y*tileset.getTileSize().y);
        target.draw(sprite);
      }
    }

  }
};

