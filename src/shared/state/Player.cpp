#include "Player.h"
#include <iostream>
#include <vector>
#include <algorithm>


namespace state {
	int Player::count = 0;	
	
	Player::Player (Cards existingCards){
		id = count;
		count++;
		oil = 0.f;
		money = 0.f;
		name = "Player "+std::to_string(count);
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
	
	void Player::addOwnedFieldObject(FieldObject* newFieldObject){
		auto match = std::find(ownedFieldObjects.begin(), ownedFieldObjects.end(), newFieldObject);
 
  		if(match != ownedFieldObjects.end()) {
    		std::cout << "This FieldObject already belong to this player" << std::endl;
  		} 
		else {
			ownedFieldObjects.push_back(newFieldObject);
  		}
	}
	void Player::removeOwnedFieldObject(FieldObject* deletedFieldObject){
		auto match = std::find(ownedFieldObjects.begin(), ownedFieldObjects.end(), deletedFieldObject);
 
  		if(match != ownedFieldObjects.end()) {
    		ownedFieldObjects.erase(match);
  		} 
		else {
    		std::cout << "This FieldObject does not belong to this player" << std::endl;
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
	int Player::getId(){
		return id;

	}
};
