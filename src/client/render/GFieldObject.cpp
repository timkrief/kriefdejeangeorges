

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
	
    GFieldObject::GFieldObject (){
    }
    GFieldObject::GFieldObject (std::shared_ptr<state::FieldObject> fieldObject):
        fieldObject(fieldObject),
        position(sf::Vector2i(-1,-1)),
        scale(1.f){
    }
    void GFieldObject::setPosition(sf::Vector2i vec){
    	position = vec;
    }
    void GFieldObject::setScale(float val){
    	scale = val;
    }
    void GFieldObject::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    	
    	sf::Sprite sprite;
    	
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
                sprite = sf::Sprite(*(TextureManager::getTexture("buildings")), rectangle);
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
                sprite = sf::Sprite(*(TextureManager::getTexture("units")), rectangle);
            }
        }
        if(position.x <0){
		    if((int)fieldObject->getObjectType()<4){/*le field object est un building*/
		    	sprite.setPosition(sf::Vector2f(fieldObject->getPosition()) * 16.f);
		    } else if((int)fieldObject->getObjectType()==5){/*le fieldobject est une unit*/
				sprite.setPosition(
				    sf::Vector2f(
				        fieldObject->getPosition().x * 16,
				        fieldObject->getPosition().y * 16 - 2
				    )
				);
			}
		} else {
			sprite.setPosition(sf::Vector2f(position));
			sprite.setScale(scale, scale);
		}
		target.draw(sprite);
    }
    int GFieldObject::getMovePoints(){
		return fieldObject->getMovePoints();
	}
    int GFieldObject::getNormalMovePoints(){
		return fieldObject->getNormalMovePoints();
	}
};

