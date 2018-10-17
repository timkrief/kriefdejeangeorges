#include "Player.h"



namespace state {
	Player::counter=0;
	Player::Player (Cards existingCards){
		oil=0.f;
		money=0.f;
		name="Player "+std::to_string(counter);
		
		id=counter;
		counter++;

	}
	
	Player::~Player(){
		counter--;

	}


	void Player::setMoney (float amount){
		if (amount>=0.f){
			money=amount;
		}
		else{
			money=0.f;
		}
	}
	
   	void Player::setOil (float amount){
		if (amount>=0.f){
			oil=amount;
		}
		else{
			oil=0.f;
		}
	}
	int Player::getId(){
		return id;

	}
};
