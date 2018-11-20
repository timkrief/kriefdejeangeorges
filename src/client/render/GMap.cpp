#include "GMap.h"
#include "TextureManager.h"

namespace render {

  GMap::GMap(){
  
  }

  void GMap::draw(sf::RenderTarget& target, sf::RenderStates states){
    //states.texture = &m_texture;
    //target.draw(m_vertices, states);
    TextureManager::loadTexture("mapTexture", "./res/sprites/mapTileset.png");
    sf::Sprite sprite(*(TextureManager::getTexture("mapTexture")));
    








  }
};

