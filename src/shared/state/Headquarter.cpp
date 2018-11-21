#include "Headquarter.h"
#include "Player.h"
#include "GameState.h"
#include "Town.h"
namespace state {
  Headquarter::Headquarter(){
  
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
  void Headquarter::captured (int besiegingPlayer, GameState &gamestate){
    gamestate.getPlayer(owner)->removeOwnedFieldObject(this);
    Town(this, besiegingPlayer, gamestate);
    
    
    //TO DO
    //Delete this headquarter
    //~Headquarter();
    //MODIFY THE GAMESTATE SOMEHOW TO MAKE THE BESIEGED PLAYER LOOSE
    //END TO DO

  }


};
