#include <iostream>
#include <SFML/Graphics.hpp>
#include "state.h"
#include "render.h"
#include "engine.h"
using namespace std;
using namespace state;
using namespace render;
using namespace engine;

void testSFML();

int testRender(GameState& state);
void testPlayer(Cards cards);
int testMapLoaded(Map map);
void testEngine(GameState& state);
int testsprite();
