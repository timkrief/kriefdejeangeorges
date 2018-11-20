

#include <SFML/Graphics.hpp>
#include <iostream>

#include "GState.h"
#include "state/GameState.h"
#include "GFieldObject.h"

namespace render {

  GFieldObject::GFieldObject (){
      position.x = 0.f;
      position.y =  0.f;
  }


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
  

};

