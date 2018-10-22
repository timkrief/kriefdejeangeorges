#include "Cards.h"
#include "yaml-cpp/yaml.h"
#include <iostream>

#include "Card.h"

namespace state {
	
    Cards::Cards(std::string cardsResPath){
		YAML::Node cards = YAML::LoadFile(cardsResPath)["cards"];
		std::cout << cards[0]["title"]["string"]["fr"].as<std::string>() << std::endl;
		
		for(YAML::const_iterator it = cards.begin(); it != cards.end(); ++it) {
			std::string key = it->first.as<std::string>();       // <- key
			std::cout << key << std::endl; // <- value
		}
	}
	
    Card* Cards::getCard (int id){
		return &cards[id];
	}
}
