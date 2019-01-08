

#include <SFML/Graphics.hpp>
#include <iostream>

#include "GState.h"
#include "state/GameState.h"
#include "GFieldObject.h"

#include "TextureManager.h"
#include "state/Tileset.h"
#include "state/Unit.h"
#include <sys/time.h> 

namespace render {

	state::Tileset GFieldObject::buildingsTileset("./res/tilesets/buildings.json");
	state::Tileset GFieldObject::unitsTileset("./res/tilesets/units.json");
	
    GFieldObject::GFieldObject (std::shared_ptr<state::FieldObject> fieldObject):
        fieldObject(fieldObject){
    }

    void GFieldObject::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        
        struct timeval tp;
        gettimeofday(&tp, NULL);
        int time = (tp.tv_sec * 1000 + tp.tv_usec / 1000) % 86400000;
        
        int tileId = -1;
        
        if((int)fieldObject->getObjectType()<4){/*le field object est un building*/
            unsigned int tmpNbTiles = buildingsTileset.getColumns() * buildingsTileset.getRows();
            for(unsigned int i = 0; i < tmpNbTiles; i++){
                std::shared_ptr<state::Tile> tile = buildingsTileset.getTile(i);
                if(tile->attributes["objectType"] == (int)fieldObject->getObjectType() && tile->attributes["player"] == fieldObject->getOwner() ){
                    tileId = i;
                    break;
                }
            }
            if(tileId != -1){
                sf::IntRect rectangle = buildingsTileset.getTileIntRect(tileId, time);
                sf::Sprite sprite(*(TextureManager::getTexture("buildings")), rectangle);
                
                sprite.setPosition(sf::Vector2f(fieldObject->getPosition()) * 16.f);
                target.draw(sprite);
            }
        } else if((int)fieldObject->getObjectType()==5){/*le fieldobject est une unit*/
        
            unsigned int tmpNbTiles = unitsTileset.getColumns() * unitsTileset.getRows();
            for(unsigned int i = 0; i < tmpNbTiles; i++){
                std::shared_ptr<state::Tile> tile = unitsTileset.getTile(i);
                if(tile->attributes["direction"] == (int)fieldObject->getDirection() && tile->attributes["player"] == fieldObject->getOwner()){
                    tileId = i;
                    break;
                }
            }
            if(tileId != -1){
                sf::IntRect rectangle = unitsTileset.getTileIntRect(tileId, time);
                sf::Sprite sprite(*(TextureManager::getTexture("units")), rectangle);
                
                sprite.setPosition(
                    sf::Vector2f(
                        fieldObject->getPosition().x * 16,
                        fieldObject->getPosition().y * 16 - 2
                    )
                );
                target.draw(sprite);
            }
        }
        if(tileId == -1){
            sf::RectangleShape rect(sf::Vector2f(16,16));
            rect.setPosition(sf::Vector2f(fieldObject->getPosition()) * 16.f);
            rect.setFillColor(sf::Color::Blue);
            target.draw(rect);
        }
    }
/*

    void GFieldObject::setSprite (state::FieldObject* fieldObject){
        sf::Texture texture;

    //---
        switch (fieldObject->getObjectType()) {
            
            case state::ObjectType::HEADQUARTER: {
                
                //sprite set texture with TextureManager
                //texture.loadFromFile("");
                //sprite(texture);                
                break;
            }
            case state::ObjectType::TOWN: {
                
                //sprite set texture with TextureManager
                //texture.loadFromFile("");
                //sprite(texture);                
                break;
            }

            case state::ObjectType::FACTORY: {
                
                //sprite set texture with TextureManager
                //texture.loadFromFile("");
                //sprite(texture);                
                break;
            }
            
            case state::ObjectType::OILWELL: {
                
                //sprite set texture with TextureManager
                //texture.loadFromFile("");
                //sprite(texture);                
                break;
            }
            
            case state::ObjectType::INSTALLATION: {
                
                //sprite set texture with TextureManager
                //sprite(texture);                        
                break;
            }        
            case state::ObjectType::UNIT: {
                //direction = fieldobject->getDirection();
        
                //sprite set texture with TextureManager
                //texture.loadFromFile("");
                //sprite(texture);                        
                break;
            } 
            default:{
                std::cout << "Error: the Objectype does not exist. If it is a new ObjectType please modify GFieldObject.cpp" << std::endl;
                break;
            }
        }
    }

  void GFieldObject::setPosition (state::FieldObject* fieldobject){
      position = fieldobject->getPosition();
  }
  */

};

