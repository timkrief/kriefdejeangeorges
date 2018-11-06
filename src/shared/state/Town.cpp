#include "Town.h"

namespace state {
  Town::Town(){
  
    moneyProduction = 0;
  }
  Town::Town(Headquarter *formerHeadquarter, int besiegingPlayer, GameState &gamestate ){
    position = &formerHeadquarter->getPosition();
    moneyProduction = &formerHeadquarter->getMoneyProduction();

    gamestate.getPlayer(besiegingPlayer).addOwnedFieldObject(this);
    owner = besiegingPlayer;

  }


  void Town::setMoneyProduction (int amount){
    if (moneyProduction >= 0){
      moneyProduction = amount;
    }
    else{
      moneyProduction = 0;
    }
  }
  int Town::getMoneyProduction()  {
    return( moneyProduction );

  }

};

