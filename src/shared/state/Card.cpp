#include "Card.h"

namespace state {

  /// class Card - 
  
	Card::Card () {} // id -1 means the card does not exist
	
	Card::Card (std::string title, int cost, std::string description, CardType type) :
		title(title),
		cost(cost),
		description(description),
		type(type) { }
		
    void Card::playCard () {}
    
    Card::~Card () {
    
    }
};
