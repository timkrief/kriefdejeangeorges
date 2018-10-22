#include "OilWell.h"

namespace state {
  OilWell::OilWell(){
  
    oilProduction = 0;
  }
  void OilWell::setOilProduction (int amount){
    if (oilProduction>=0){
      oilProduction = amount;
    }
    else{
      oilProduction=0;
    }
  }
  void OilWell::captured (int besiegingPlayer){
    //change the owner of the building and the ownedFieldObject of the previous
    //owner player 
    //TO DO
    //owner ownerFieldObject remove this fieldobject
    //END TO DO
    owner = besiegingPlayer;


  }

};


