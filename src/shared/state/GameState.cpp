#include "GameState.h"

namespace state {
  GameState::GameState() : map(), existingCards("res/cards.yaml","fr"){
  }


  Player GameState::getPlayer(int id){
    return players[id] ;

  }

};