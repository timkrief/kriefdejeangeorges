#include "Cards.h"
#include "yaml-cpp/yaml.h"

#include "Card.h"

#include "UnitCard.h"
#include "EquipmentCard.h"
#include "InstallationCard.h"
#include "SupportCard.h"

#include "CardType.h"
#include <iostream>

namespace state {
	
    Cards::Cards(std::string cardsResPath, std::string lang = "en"){
		
		YAML::Node parsedCardsFile = YAML::LoadFile(cardsResPath); // Parse the file
		
		YAML::Node cardTypeStr2Int = parsedCardsFile["CardType"];
		YAML::Node unitTypeStr2Int = parsedCardsFile["UnitType"];
		YAML::Node parsedCardList = parsedCardsFile["cards"];
		
		size = 0;
		
		for(YAML::const_iterator it = parsedCardList.begin(); it != parsedCardList.end(); ++it) {
		    unsigned int knownSize = it->first.as<unsigned int>() + 1;
			size = std::max(size, knownSize);
		}
		
		cards.resize(size);
		
		for(YAML::const_iterator it = parsedCardList.begin(); it != parsedCardList.end(); ++it) {
			
			// id
			int id = it->first.as<int>();
			
			// Title
			std::string title = "No title found";
			
			if(it->second["title"]){
				if(it->second["title"][lang]){
					title = it->second["title"][lang].as<std::string>();
				} else if (it->second["title"]["en"]){
					title = it->second["title"]["en"].as<std::string>();
				}
			}
			
			// Cost
			int cost = it->second["cost"] ? 
				it->second["cost"].as<int>() : 
				0; // Cost 0 by default
				
			// Cost
			std::string description = "";
		
			if(it->second["description"]){
				if(it->second["description"][lang]){
					description = it->second["description"][lang].as<std::string>();
				} else if (it->second["description"]["en"]){
					description = it->second["description"]["en"].as<std::string>();
				}
			}
			
			// Type
			CardType type = (CardType)cardTypeStr2Int[
				it->second["type"] ? 
					it->second["type"].as<std::string>() : 
					"UNIT" // Type is UNIT by default
			].as<int>(); 
			
			switch (type) {
				case CardType::EQUIPMENT: {
					
					// Level
					int level = it->second["level"] ? 
						it->second["level"].as<int>() :
						1; // Level 1 by default
					
					// Strengths
					const std::size_t strengthsListSize = it->second["strengths"] ? it->second["strengths"].size() : 0;
						
					std::vector<UnitType> strengths;
					
					for (std::size_t i = 0; i < strengthsListSize; i++) {
						strengths.push_back((UnitType)unitTypeStr2Int[it->second["strengths"][i].as<std::string>()].as<int>());
					}
					
					// Head Count
					int headCount = it->second["headCount"] ? 
						it->second["headCount"].as<int>() :
						0; // 0 headcount by default
						
					cards[id] = std::make_shared<EquipmentCard>(title, cost, description, level, strengths, headCount);
					
					break;
				} case CardType::INSTALLATION: {
					
					// Stop Opponent
					bool stopOpponent = it->second["stopOpponent"] ? 
						it->second["stopOpponent"].as<bool>() :
						false; // By default, don't stop opponent
					
					// Damage
					float damage = it->second["damage"] ? 
						it->second["damage"].as<float>() :
						0.f; // 0 damage by default
					
					// Iterations
					int iterations = it->second["iterations"] ? 
						it->second["iterations"].as<int>() :
						1; // 1 iteration by default
						 
					cards[id] = std::make_shared<InstallationCard>(title, cost, description, stopOpponent, damage, iterations);
					
					break;
				} case CardType::SUPPORT: {
					
					// Damage
					float damage = it->second["damage"] ? 
						it->second["damage"].as<float>() :
						0.f; // 0 damage by default
						
					// Heal
					float heal = it->second["heal"] ? 
						it->second["heal"].as<float>() :
						0.f; // 0 heal by default
					
					// Money Loss
					int moneyLoss = it->second["moneyLoss"] ? 
						it->second["moneyLoss"].as<int>() :
						0; // 0 money loss by default
					
					// Money Gain
					int moneyGain = it->second["moneyGain"] ? 
						it->second["moneyGain"].as<int>() :
						0; // 0 money gain by default
					
					// Oil Loss
					int oilLoss = it->second["oilLoss"] ? 
						it->second["oilLoss"].as<int>() :
						0; // 0 oil loss by default
					
					// Oil Gain
					int oilGain = it->second["oilGain"] ? 
						it->second["oilGain"].as<int>() :
						0; // 0 oil gain by default
						
					cards[id] = std::make_shared<SupportCard>(title, cost, description, damage, heal, moneyLoss, moneyGain, oilLoss, oilGain);
					
					break;
				} default: { // UNIT
					
					// Level
					int level = it->second["level"] ? 
						it->second["level"].as<int>() :
						1; // Level 1 by default
						
					// UnitType
					UnitType unitType = (UnitType)unitTypeStr2Int[
						it->second["unitType"] ? 
							it->second["unitType"].as<std::string>() : 
							"SOLDIER" // unitType is SOLDIER by default
					].as<int>(); 
					
					// Strengths
					const std::size_t strengthsListSize = it->second["strengths"] ? it->second["strengths"].size() : 0;
						
					std::vector<UnitType> strengths;
					
					for (std::size_t i = 0; i < strengthsListSize; i++) {
						strengths.push_back((UnitType)unitTypeStr2Int[it->second["strengths"][i].as<std::string>()].as<int>());
					}
					
					// Moves by turn
					int movesByTurn = it->second["movesByTurn"] ? 
						it->second["movesByTurn"].as<int>() :
						1; // 1 movesByTurn by default
						
					// Oil cost
					int oilCost = it->second["oilCost"] ? 
						it->second["oilCost"].as<int>() :
						0; // 1 movesByTurn by default
					
					cards[id] = std::make_shared<UnitCard>(title, cost, description, level, unitType, strengths, movesByTurn, oilCost);
	
					break;
				}
			}
			
		}
	}
	
    std::shared_ptr<Card> Cards::getCard (int id){
		return cards[id];
	}
	
	Cards::~Cards(){
	
	}
}
