#include "Building.h"
#include "Player.h"
#include "GameState.h"

namespace state {
  Building::Building(){
    health = 1;
  }


  void Building::captured (int besiegingPlayer, GameState &gamestate){
    
    gamestate.getPlayer(owner).removeOwnedFieldObject(this);
    gamestate.getPlayer(besiegingPlayer).addOwnedFieldObject(this);
    //threadable
    owner = besiegingPlayer;


  }

};
