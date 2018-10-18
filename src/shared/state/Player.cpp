#include "Player.h"



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
