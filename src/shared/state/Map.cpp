#include "Map.h"
#include "yaml-cpp/yaml.h"
#include <iostream>
#include <stdlib.h> 

namespace state {
    Map::Map() {

    }

    Map::Map(std::string mapFilePath) {
		    YAML::Node parsedMapFile = YAML::LoadFile(mapFilePath); // Parse the file
		    const size_t nbOfLayers = parsedMapFile["layers"].size();
		    
		    YAML::Node field;
		    for(size_t i = 0; i < nbOfLayers; i++) {
		        if(parsedMapFile["layers"][i]["name"].as<std::string>() == "field"){
		            field = parsedMapFile["layers"][i];
		            break;
		        }
		        if(i-1 == nbOfLayers){
		            throw std::invalid_argument("No field layer, map initialization failed.");
		        }
		    }
		    
        size = sf::Vector2u((unsigned int)field["width"].as<int>(), (unsigned int)field["height"].as<int>());
        
        const size_t dataLen = size.x * size.y;
        
        data = (unsigned int*) calloc(dataLen, sizeof(unsigned int)); // we may check for failure here
        
        for(size_t i = 0; i < dataLen; i++) {
            data[i] = field["data"][i].as<int>();
        }
            
		    std::cout << data[4] << std::endl;
    }
    
    Map::~Map() {
        free(data);
        data = NULL;
    }
    
    unsigned int* Map::getData () {
        return data;
    }
    sf::Vector2u Map::getSize () {
        return size;
    }
};
