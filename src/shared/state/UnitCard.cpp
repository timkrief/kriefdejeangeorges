#include "UnitCard.h"
#include "CardType.h"
#include <iostream>

namespace state {
	UnitCard::UnitCard (
		int id, 
		std::string title, 
		int cost, 
		std::string description, 
		int level, 
		UnitType unitType, 
		UnitType* strengths, 
		int movesByTurn, 
		int oilCost
	) :
		Card(id, title, cost, description, CardType::UNIT) , 
		level(level), 
		unitType(unitType),
		strengths(strengths), 
		movesByTurn(movesByTurn), 
		oilCost(oilCost) 
	{ 
		std::cout << std::endl << "---------" << std::endl;
		std::cout << "id: " << id << std::endl;
		std::cout << "title: " << title << std::endl;
		std::cout << "cost: " << cost << std::endl;
		std::cout << "description: " << description << std::endl;
		std::cout << "level: " << level << std::endl;
		std::cout << "movesByTurn: " << movesByTurn << std::endl;
		std::cout << "oilCost: " << oilCost << std::endl;
		std::cout << "---------" << std::endl << std::endl;
	}
	void UnitCard::playCard() {}
};