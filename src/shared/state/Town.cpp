#include "Town.h"
#include "Headquarter.h"

#include "GameState.h"


namespace state {
  Town::Town() : Building(){
    moneyProduction = 0;
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

