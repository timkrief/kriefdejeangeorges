#include "EquipmentCard.h"
#include "CardType.h"
#include "UnitType.h"
#include <iostream>

namespace state {
    EquipmentCard::EquipmentCard() : Card() {}
    
    EquipmentCard::EquipmentCard (
		std::string title, 
		int cost, 
		std::string description, 
		int level,
		std::vector<UnitType> strengths, 
		int headCount
	) :
		Card(title, cost, description, CardType::EQUIPMENT) , 
		level(level), 
		strengths(strengths),
		headCount(headCount)
	{ /*
		//std::cout << std::endl << "---------" << std::endl;
		//std::cout << "title: " << title << std::endl;
		//std::cout << "cost: " << cost << std::endl;
		//std::cout << "description: " << description << std::endl;
		//std::cout << "level: " << level << std::endl;
		//std::cout << "headCount: " << headCount << std::endl;
		//std::cout << "---------" << std::endl << std::endl;
		*/
	}
	
    void EquipmentCard::playCard () { } 
};
