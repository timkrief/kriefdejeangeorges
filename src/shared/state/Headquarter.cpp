#include "Headquarter.h"
#include "Player.h"
#include "GameState.h"
#include "Town.h"
namespace state {
  Headquarter::Headquarter() : Building(){
  
    moneyProduction = 0;
  }
  
  Headquarter::~Headquarter(){

  }
  
  void Headquarter::setMoneyProduction (int amount){
    if (moneyProduction>=0){
    moneyProduction = amount;
    }
    else{
      moneyProduction=0;
    }
  }



  int Headquarter::getMoneyProduction()  {
    return( moneyProduction );

  }

};
