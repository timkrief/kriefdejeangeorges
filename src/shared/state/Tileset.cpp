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
		tileheight = parsedTilesetFile["tileheight"].as<int>();
		
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
    
    std::shared_ptr<Tile> Tileset::getTile (int id){
		return tiles[id];
	}
	
    std::string Tileset::getResourcePath () {
        return resourcePath;    
    }
    int Tileset::getColumns () {
        return columns;    
    }
    int Tileset::getTileheight () {
        return tileheight;    
    }
};
