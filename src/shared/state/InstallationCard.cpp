#include "InstallationCard.h"
#include "CardType.h"
#include <iostream>

namespace state {

    InstallationCard::InstallationCard() : Card() {}
    
    InstallationCard::InstallationCard (
		std::string title, 
		int cost, 
		std::string description, 
		bool stopOpponent, 
		float damage, 
		int iterations
	) :
		Card(title, cost, description, CardType::INSTALLATION) , 
		stopOpponent(stopOpponent), 
		damage(damage), 	
		iterations(iterations)
	{ /*
		//std::cout << std::endl << "---------" << std::endl;
		//std::cout << "title: " << title << std::endl;
		//std::cout << "cost: " << cost << std::endl;
		//std::cout << "description: " << description << std::endl;
		//std::cout << "stopOpponent: " << stopOpponent << std::endl;
		//std::cout << "damage: " << damage << std::endl;
		//std::cout << "iterations: " << iterations << std::endl;
		//std::cout << "---------" << std::endl << std::endl;
		*/
	}
	
    void InstallationCard::playCard () { }
};
