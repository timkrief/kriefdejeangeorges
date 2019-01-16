#include "Tileset.h"
#include "yaml-cpp/yaml.h"

#include "Tile.h"
#include <iostream>
#include <stdlib.h>

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
	   
		////std::cout << resourcePath << std::endl;
		
		columns = parsedTilesetFile["columns"].as<int>();
		rows = parsedTilesetFile["imageheight"].as<int>() / parsedTilesetFile["tileheight"].as<int>();
		tileSize = sf::Vector2u(
		    parsedTilesetFile["tileheight"].as<int>(),
		    parsedTilesetFile["tilewidth"].as<int>()
		);
		resourceSize = sf::Vector2u(
		    parsedTilesetFile["imageheight"].as<int>(),
		    parsedTilesetFile["imagewidth"].as<int>()
		);
		
		YAML::Node tileproperties = parsedTilesetFile["tileproperties"];
		tiles.resize(parsedTilesetFile["tilecount"].as<int>(), std::make_shared<Tile>());
		for(YAML::const_iterator it = tileproperties.begin(); it != tileproperties.end(); ++it) {
			// id
			int id = it->first.as<int>();
			tiles[id] = std::make_shared<Tile>();
			
		    for(YAML::const_iterator attributesIt = it->second.begin(); attributesIt != it->second.end(); ++attributesIt) {
		        tiles[id]->attributes[attributesIt->first.as<std::string>()] = attributesIt->second.as<int>();
		    }
				
		}
		
		YAML::Node tileAnimation = parsedTilesetFile["tiles"];
		
		int tmpDuration = -1;
		int tmpTileId = -1;
        for(YAML::const_iterator it = tileAnimation.begin(); it != tileAnimation.end(); ++it) {
        // id
            int id = it->first.as<int>();
            
            if(it->second["animation"]){
                
                for (std::size_t i = 0; i < it->second["animation"].size(); i++) {
                    
                    for(YAML::const_iterator animIt = it->second["animation"][i].begin(); animIt != it->second["animation"][i].end(); ++animIt) {
                        if(animIt->first.as<std::string>() == "duration") {
                            tmpDuration = animIt->second.as<int>();
                        } else if(animIt->first.as<std::string>() == "tileid") {
                            tmpTileId = animIt->second.as<int>();
                        }
                    }
                    if(tmpDuration != -1 && tmpTileId != -1){
                        
                        tiles[id]->frameDuration.push_back(tmpDuration);
                        tiles[id]->frameTileId.push_back(tmpTileId);
                        
                        tiles[id]->animationDuration += tmpDuration;
                    }
                    tmpDuration = -1;
                    tmpTileId = -1;
                }
            }
        }
    }
    
    std::shared_ptr<Tile> Tileset::getTile (unsigned int id) const{
		return tiles[id];
	}
	
    std::string Tileset::getResourcePath () const{
        return resourcePath;    
    }
    unsigned int Tileset::getColumns () const{
        return columns;    
    }
    unsigned int Tileset::getRows () const{
        return rows;    
    }
    unsigned int Tileset::getTileheight () const{
        return tileSize.x;    
    }
    sf::Vector2u Tileset::getTileSize () const{
        return tileSize;    
    }
    sf::Vector2u Tileset::getTilePosition(unsigned int id, int time) const{
        if(tiles[id]->animationDuration > 0){
            time %= tiles[id]->animationDuration;
            int frame = 0;
            
            id = tiles[id]->frameTileId[0];
            while(time >= 0){
                time -= tiles[id]->frameDuration[frame];
                frame++;
            }
            id = tiles[id]->frameTileId[frame-1];
        }
        return sf::Vector2u(
            tileSize.x * (id % getColumns()), 
            tileSize.y * ((int)(id / getColumns()))
        );
    }
    sf::IntRect Tileset::getTileIntRect(unsigned int id, int time) const{
        id %= (columns*rows);
        
        sf::Vector2u tilePosition = getTilePosition(id, time);
        sf::Vector2u tileSize = getTileSize();
        return sf::IntRect(
            tilePosition.x,
            tilePosition.y,
            tileSize.x,
            tileSize.y
        );
    }
};
