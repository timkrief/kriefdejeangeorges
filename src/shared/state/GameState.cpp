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
    return players[id + 1] ;
  }
  unsigned int GameState::getPlayerCount(){
    return Player::getCount() - 1;
  }
  unsigned int GameState::getTurn(){
    return turn;
  }
  unsigned int GameState::getPlayerTurnId(){
    return getTurn() % getPlayerCount();
  }
  void GameState::endTurn(bool backInTime){
    turn+= backInTime ? -1 : 1;
  }
};
