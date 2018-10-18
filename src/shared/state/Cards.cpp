#include "Cards.h"

namespace state {
  class Card;
}

#include "Card.h"

namespace state {
	
    Cards::Cards(std::string cardsResPath){
		
	}
	
    Card* Cards::getCard (int id){
		return &cards[id];
	}
}
