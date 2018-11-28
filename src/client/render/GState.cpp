#include "GState.h"

namespace render {
  GState::GState(std::shared_ptr<state::GameState> state):
    gmap(state->getMap()),
    state(state){
    for(size_t i=0; i<state->getPlayerCount(); i++){
        gplayers.push_back(state->getPlayer(i));
    }
  }

  GMap& GState::getGMap(){
    return gmap;
  }
  std::vector<GPlayer>& GState::getPlayers(){
    return gplayers;
  }
  
};

