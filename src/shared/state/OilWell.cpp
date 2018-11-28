#include "OilWell.h"

namespace state {
  OilWell::OilWell(): Building(){
  
    oilProduction = 0;
  }
  void OilWell::setOilProduction (int amount){
    if (oilProduction>=0){
      oilProduction = amount;
    }
    else{
      oilProduction=0;
    }
  }
 
};


