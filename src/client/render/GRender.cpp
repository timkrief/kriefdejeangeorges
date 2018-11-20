
#include "GRender.h"
#include <SFML/Graphics.hpp>
#include "GState.h"
#include "state/GameState.h"
#include "state/ObjectType.h"


namespace render {

  GRender::GRender():
  window(sf::VideoMode(600, 800), "Until last barrel")
  
  {
    window.setFramerateLimit(60);

  }




  void GRender::display (GState g){
      //window.clear();
      //window.draw(g::state::map);

      window.display();    

  }

};

