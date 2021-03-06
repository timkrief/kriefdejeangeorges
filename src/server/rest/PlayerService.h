// Generated by dia2code
#ifndef REST__PLAYERSERVICE__H
#define REST__PLAYERSERVICE__H

#include <string>
#include <vector>
#include <json/json.h>

namespace rest {
  class AbstractService;
}

#include "HttpStatus.h"
#include "AbstractService.h"

namespace rest {

  /// class PlayerService - 
  class PlayerService : public rest::AbstractService {
    // Attributes
  public:
    std::vector<std::string> players;
    // Operations
  public:
    PlayerService ();
    HttpStatus get (Json::Value& out, int id) const;
    HttpStatus post (const Json::Value& in, int id);
    HttpStatus put (Json::Value& out, const Json::Value& in);
    HttpStatus remove (int id);
  };

};

#endif
