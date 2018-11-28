#include "GMap.h"
#include "TextureManager.h"
#include "state/Tileset.h"

namespace render {

  GMap::GMap(std::shared_ptr<state::Map> map):
    map(map)
  {
    
    TextureManager::loadTexture("mapTexture", "./res/sprites/mapTileset.png");
        
  }

  void GMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    
  
    state::Tileset tileset= map->getTileset();

    for(unsigned int x = 0; x < map->getSize().x; x++){
      for(unsigned int y = 0; y < map->getSize().y; y++){
        
        sf::IntRect rectangle = tileset.getTileIntRect(map->getData(sf::Vector2u(x,y)));
        sf::Sprite sprite(*(TextureManager::getTexture("mapTexture")), rectangle);
        sprite.setPosition(x*16,y*16);
        target.draw(sprite);
      }
    }

  }
};

