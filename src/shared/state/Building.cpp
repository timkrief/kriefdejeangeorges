#include "Building.h"

namespace state {
  Building::Building(){
    health = 1;
  }


  void Building::captured (int besiegingPlayer){
    //change the owner of the building and the ownedFieldObject of the previous
    //owner player 
    //TO DO
    //owner ownerFieldObject remove this fieldobject
    //END TO DO
    owner = besiegingPlayer;


  }

};
