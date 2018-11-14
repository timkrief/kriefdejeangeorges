#include "Map.h"
#include "yaml-cpp/yaml.h"
#include <iostream>
#include <stdlib.h> 

namespace state {
    Map::Map() {

    }

    Map::Map(std::string mapFilePath, std::string layerName) {
	    YAML::Node parsedMapFile = YAML::LoadFile(mapFilePath); // Parse the file
	    const size_t nbOfLayers = parsedMapFile["layers"].size();
	    
	    YAML::Node layer;
	    for(size_t i = 0; i < nbOfLayers; i++) {
	        if(parsedMapFile["layers"][i]["name"].as<std::string>() == layerName){
	            layer = parsedMapFile["layers"][i];
	            
                size_t lastSlashPosition;
                lastSlashPosition = mapFilePath.find_last_of("/"); // system specific
                std::string mapDirectoryPath = mapFilePath.substr(0, lastSlashPosition);
                std::string pathRelativeToMap = parsedMapFile["tilesets"][i]["source"].as<std::string>();
                std::string tilesetResPath = mapDirectoryPath + "/" + pathRelativeToMap;
                
	            tileset = Tileset(tilesetResPath);
	            break;
	        }
	        if(i-1 == nbOfLayers){
	            throw std::invalid_argument("Layer " + layerName + " not found, map initialization failed.");
	        }
	    }
	    
		    
        size = sf::Vector2u((unsigned int)layer["width"].as<int>(), (unsigned int)layer["height"].as<int>());
        
        const size_t dataLen = size.x * size.y;
        
        data = (unsigned int*) calloc(dataLen, sizeof(unsigned int)); // we may check for failure here
        
        for(size_t i = 0; i < dataLen; i++) {
            data[i] = layer["data"][i].as<int>();
        }
        
        std::cout << data[4] << std::endl;
    }
    
    Map::~Map() {
    
    }
    
    sf::Vector2u Map::getSize () {
        return size;
    }
    unsigned int* Map::getData () {
        return data;
    }
    std::shared_ptr<Tile> Map::getTile(int x, int y){
        return tileset.getTile(data[x + size.x * y]);
    }
};
