#include "GState.h"

namespace render {

  
  
  GState::GState(std::shared_ptr<state::GameState> state):   gmap(std::make_shared<state::Map>(state->getMap())), state(state)
  {
  }

  GMap& GState::getGMap(){
    return gmap;
  }
  
};

