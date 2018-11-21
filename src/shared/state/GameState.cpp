#include "GameState.h"
#include <iostream>

namespace state {
  GameState::GameState(std::string mapPath, std::string lang) : 
    map(std::make_shared<Map>(mapPath, "field")), 
    existingCards(std::make_shared<Cards>("res/cards.yaml", lang)){
    turn = 0;
  }

  std::shared_ptr<Map> GameState::getMap(){
    return map;
  }
  std::shared_ptr<Player> GameState::getPlayer(int id){
    return players[id] ;
  }
  std::shared_ptr<FieldObjects> GameState::getFieldObjects(){
    return fieldObjects;
  }
  void GameState::endTurn(){
    turn++;
    std::cout << "nouveau tour: " << turn << std::endl;
  }
};
