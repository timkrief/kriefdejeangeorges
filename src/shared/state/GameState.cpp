#include "GameState.h"
#include <iostream>

namespace state {
  GameState::GameState(std::string mapPath, std::string lang) : 
    map(std::make_shared<Map>(mapPath, "field")), 
    existingCards(std::make_shared<Cards>("res/cards.yaml", lang)){
    turn = 0;
    players.push_back(std::make_shared<Player>());
  }

  std::shared_ptr<Map> GameState::getMap(){
    return map;
  }
  void GameState::addPlayer(std::string deckPath){
    players.push_back(std::make_shared<Player>(existingCards, deckPath));
  }
  void GameState::addPlayer(std::shared_ptr<Player> player){
    players.push_back(player);
  }
  std::shared_ptr<Player> GameState::getPlayer(int id){
    return players[id] ;
  }
  unsigned int GameState::getPlayerCount(){
    return Player::getCount();
  }
  void GameState::endTurn(){
    turn++;
    std::cout << "nouveau tour: " << turn << std::endl;
  }
};
