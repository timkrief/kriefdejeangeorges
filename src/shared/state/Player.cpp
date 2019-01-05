#include "Player.h"
#include <iostream>
#include <vector>
#include <algorithm>


namespace state {
	unsigned int Player::count = 0;	

	void Player::InitPlayer(){
		
		count++;
		id = count;
		
		oil = 0.f;
		money = 0.f;
		name = "Player "+std::to_string(count);
	}
	
	Player::Player (){
	    InitPlayer();
	}
	Player::Player (std::shared_ptr<Cards> existingCards, std::string deckPath){
	    InitPlayer();
	}
	
	Player::~Player(){
		count--;
	}

	int Player::getMoney (){
		return int(money);
	}

	void Player::setMoney (float amount){
		if (amount >= 0.f){
			money = amount;
		}
		else{
			money = 0.f;
		}
	}
	
   	int Player::getOil (){
		return int(oil);
	}
   	void Player::setOil (float amount){
		if (amount >= 0.f){
			oil = amount;
		}
		else{
			oil = 0.f;
		}
	}
	unsigned int Player::getId(){
		return id;
	}
	std::string Player::getName(){
		return name;
	}

	std::vector<std::shared_ptr<FieldObject>> Player::getOwnedFieldObjects(){
	    return ownedFieldObjects;
	}
	
	void Player::addOwnedFieldObject(std::shared_ptr<FieldObject> newFieldObject){
		auto match = std::find(ownedFieldObjects.begin(), ownedFieldObjects.end(), newFieldObject);
 
  		if(match != ownedFieldObjects.end()) {
    		std::cout << "This FieldObject already belong to this player" << std::endl;
  		} 
		else {
			ownedFieldObjects.push_back(newFieldObject);
			newFieldObject->setOwner(id);
  		}
	}
	
	void Player::removeOwnedFieldObject(std::shared_ptr<FieldObject> deletedFieldObject){
		auto match = std::find(ownedFieldObjects.begin(), ownedFieldObjects.end(), deletedFieldObject);
 
  		if(match != ownedFieldObjects.end()) {
    		ownedFieldObjects.erase(match);
  		} 
		else {
    		std::cout << "This FieldObject does not belong to this player" << std::endl;
  		}

	}


	unsigned int Player::getCount(){
		return count;
	}

};
