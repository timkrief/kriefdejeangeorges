#include "Tileset.h"
#include "yaml-cpp/yaml.h"

#include "Tile.h"
#include <iostream>

namespace state {
    Tileset::Tileset (){
    
    }
    
    Tileset::Tileset (std::string tilesetResPath){
		YAML::Node parsedTilesetFile = YAML::LoadFile(tilesetResPath); // Parse the file
		
        size_t lastSlashPosition;
        lastSlashPosition = tilesetResPath.find_last_of("/"); // system specific
        std::string tilesetDirectoryPath = tilesetResPath.substr(0, lastSlashPosition);
        std::string pathRelativeToTileset = parsedTilesetFile["image"].as<std::string>();
        resourcePath = tilesetDirectoryPath + "/" + pathRelativeToTileset;
	            
		std::cout << resourcePath << std::endl;
		
		columns = parsedTilesetFile["columns"].as<int>();
		tileSize = sf::Vector2u(
		    parsedTilesetFile["tileheight"].as<int>(),
		    parsedTilesetFile["tilewidth"].as<int>()
		);
		resourceSize = sf::Vector2u(
		    parsedTilesetFile["imageheight"].as<int>(),
		    parsedTilesetFile["imagewidth"].as<int>()
		);
		
		YAML::Node tileproperties = parsedTilesetFile["tileproperties"];
		tiles.resize(parsedTilesetFile["tilecount"].as<int>(), std::make_shared<Tile>(0.f));
		for(YAML::const_iterator it = tileproperties.begin(); it != tileproperties.end(); ++it) {
			// id
			int id = it->first.as<int>();
			
			// Speed
			float speed = it->second["speed"] ? 
				it->second["speed"].as<float>() : 
				0.f; // Speed is 0 by default
				
			tiles[id] = std::make_shared<Tile>(speed);
		}
    }
    
    std::shared_ptr<Tile> Tileset::getTile (unsigned int id){
		return tiles[id];
	}
	
    std::string Tileset::getResourcePath () {
        return resourcePath;    
    }
    unsigned int Tileset::getColumns () {
        return columns;    
    }
    unsigned int Tileset::getTileheight () {
        return tileSize.x;    
    }
    sf::Vector2u Tileset::getTileSize () {
        return tileSize;    
    }
    sf::Vector2u Tileset::getTilePosition(unsigned int id){
        return sf::Vector2u(
            tileSize.x * (id % getColumns()), 
            tileSize.y * ((int)(id / getColumns()))
        );
    }
    sf::IntRect Tileset::getTileIntRect(unsigned int id){
        sf::Vector2u tilePosition = getTilePosition(id);
        sf::Vector2u tileSize = getTileSize();
        return sf::IntRect(
            tilePosition.x,
            tilePosition.y,
            tileSize.x,
            tileSize.y
        );
    }
};
