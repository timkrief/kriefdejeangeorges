// Generated by dia2code
#ifndef RENDER__GPLAYER__H
#define RENDER__GPLAYER__H

#include <memory>

namespace sf {
  class Drawable;
};
namespace state {
  class GameState;
};
namespace render {
  class GFieldObject;
}

#include "state/GameState.h"
#include "GFieldObject.h"

namespace render {

  /// class GPlayer - 
  class GPlayer : public sf::Drawable {
    // Associations
    // Attributes
  private:
    std::shared_ptr<state::Player> player;
    // Operations
  public:
    GPlayer (std::shared_ptr<state::Player> player);
    void draw (sf::RenderTarget& target, sf::RenderStates states) const;
  };

};

#endif
