#include "Town.h"

namespace state {
  Town::Town(){
  
    moneyProduction = 0;
  }
  Town::Town(Headquarter formerHeadquarter, int besiegingPlayer ){
   // position = formerHeadquarter.position;
   // moneyProduction = formerHeadquarter.moneyProduction;
    owner = besiegingPlayer;

  }

  void Town::setMoneyProduction (int amount){
    if (moneyProduction>=0){
      moneyProduction = amount;
    }
    else{
      moneyProduction=0;
    }
  }
  

  void Town::captured (int besiegingPlayer){
    //change the owner of the building and the ownedFieldObject of the previous
    //owner player 
    //TO DO
    //owner ownerFieldObject remove this fieldobject
    //END TO DO
    owner = besiegingPlayer;


  }

};

