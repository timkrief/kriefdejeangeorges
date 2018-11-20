#include "GameState.h"

namespace state {
  GameState::GameState(std::string mapPath, std::string lang) : 
    map(mapPath, "field"), 
    existingCards("res/cards.yaml",lang){
    
  }

  Map GameState::getMap(){
    return map;
  }
  Player GameState::getPlayer(int id){
    return players[id] ;
  }
};
