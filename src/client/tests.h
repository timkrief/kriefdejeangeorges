#include <iostream>
#include <SFML/Graphics.hpp>
#include "state.h"
#include "render.h"
using namespace std;
using namespace state;
using namespace render;
void testSFML();


int testRender(GameState& state);
void testPlayer(Cards cards);
int testMapLoaded(Map map); // rendererPrototype
int testsprite();