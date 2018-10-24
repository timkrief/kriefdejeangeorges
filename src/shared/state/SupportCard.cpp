#include "SupportCard.h"
#include "CardType.h"
#include <iostream>


namespace state {
	
    SupportCard::SupportCard (
		int id, 
		std::string title, 
		int cost, 
		std::string description, 
		float damage, 
		float heal, 
		int moneyLoss, 
		int moneyGain, 
		int oilLoss, 
		int oilGain
	) :
		Card(id, title, cost, description, CardType::SUPPORT) , 
		damage(damage), 
		heal(heal), 
		moneyLoss(moneyLoss), 
		moneyGain(moneyGain), 
		oilLoss(oilLoss), 
		oilGain(oilGain)
	{ 
		std::cout << std::endl << "---------" << std::endl;
		std::cout << "id: " << id << std::endl;
		std::cout << "title: " << title << std::endl;
		std::cout << "cost: " << cost << std::endl;
		std::cout << "description: " << description << std::endl;
		std::cout << "damage: " << damage << std::endl;
		std::cout << "heal: " << heal << std::endl;
		std::cout << "moneyLoss: " << moneyLoss << std::endl;
		std::cout << "moneyGain: " << moneyGain << std::endl;
		std::cout << "oilLoss: " << oilLoss << std::endl;
		std::cout << "oilGain: " << oilGain << std::endl;
		std::cout << "---------" << std::endl << std::endl;
	}
	
	
    void SupportCard::playCard () { }

};
