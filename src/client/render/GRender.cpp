
#include "GRender.h"
#include <SFML/Graphics.hpp>
#include "GState.h"
#include "state/GameState.h"
#include "state/ObjectType.h"
#include "GMap.h"

namespace render {

  GRender::GRender():
  window(sf::VideoMode(800, 600), "Until last barrel")
  
  {
    window.setFramerateLimit(60);

  }




  void GRender::display (GState& g){
      //window.clear();
      //GMap gmap(std::make_shared<state::Map>(g.getState().getMap()));

      window.draw(g.getGMap());
      
      std::vector<GPlayer> players = g.getPlayers();
      for(auto player: players){
        window.draw(player);
      }

      window.display();    

  }

};

