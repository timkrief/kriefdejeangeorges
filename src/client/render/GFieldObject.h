// Generated by dia2code
#ifndef RENDER__GFIELDOBJECT__H
#define RENDER__GFIELDOBJECT__H

#include <memory>
#include <SFML/Graphics.hpp>

namespace state {
  class FieldObject;
};
namespace sf {
  class Drawable;
};
namespace state {
  class Tileset;
}

#include "state/FieldObject.h"
#include "state/Tileset.h"

namespace render {

  /// class GFieldObject - 
  class GFieldObject : public sf::Drawable {
    // Associations
    // Attributes
  private:
    std::shared_ptr<state::FieldObject> fieldObject;
    static state::Tileset buildingsTileset;
    static state::Tileset unitsTileset;
    sf::Vector2i position;
    float scale;
    // Operations
  public:
    GFieldObject (std::shared_ptr<state::FieldObject> fieldObject);
    GFieldObject ();
    void draw (sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Sprite getSprite ();
    void setPosition (sf::Vector2i vec);
    void setScale (float scale);
    int getMovePoints ();
    int getNormalMovePoints ();
  };

};

#endif
