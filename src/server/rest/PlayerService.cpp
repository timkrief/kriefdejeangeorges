/** 
 * @file UserService.cpp
 * @author Philippe-Henri Gosselin
 * @date 9 décembre 2015
 * @copyright CNRS
 */

#include "PlayerService.h"
#include "ServiceException.h"

namespace rest{
	PlayerService::PlayerService () : AbstractService("/user"){
		
	}

	HttpStatus PlayerService::get (Json::Value& out, int id) const {
		throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Non implanté");
	}

	HttpStatus PlayerService::post (const Json::Value& in, int id) {
		throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Non implanté");
	}

	HttpStatus PlayerService::put (Json::Value& out,const Json::Value& in) {
		throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Non implanté");
	}

	HttpStatus PlayerService::remove (int id) {
		throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Non implanté");
	}
};
