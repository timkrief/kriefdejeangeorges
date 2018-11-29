#include "Factory.h"

namespace state {
  Factory::Factory(): Building() {
    setObjectType(ObjectType::FACTORY);
  }
};

