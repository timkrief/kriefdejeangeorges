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
  int GameState::getDistance(sf::Vector2u coordA, sf::Vector2u coordB){
    int manathan = (abs(coordA.x-coordB.x) + abs(coordA.y-coordB.y));
    
    if(manathan <= 10){
        float weight = 0;
        for(int x = std::min(coordA.x, coordB.x); x <= std::max(coordA.x, coordB.x); x++){
            for(int y = std::min(coordA.y, coordB.y); y <= std::max(coordA.y, coordB.y); y++){
                float tmp_weight = map->getTile(sf::Vector2u(x, y))->attributes["moveCost"];
                tmp_weight = tmp_weight < 0 ? 2 : 1;
                weight += tmp_weight;
            }
        }
        
        return weight/((abs(coordA.x-coordB.x)+1)*(abs(coordA.y-coordB.y)+1))*manathan;
    } else {
        return manathan;
    }
  }
};
