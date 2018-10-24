#include "Headquarter.h"

namespace state {
  Headquarter::Headquarter(){
  
    moneyProduction = 0;
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
  void Headquarter::captured (int besiegingPlayer){
    //change the owner of the building and the ownedFieldObject of the previous
    //owner player 
    //TO DO
    //owner ownerFieldObject remove this fieldobject
    //END TO DO
    owner = besiegingPlayer;


  }

};
