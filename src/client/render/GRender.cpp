
#include "GRender.h"
#include <SFML/Graphics.hpp>
#include "GState.h"
#include "state/GameState.h"
#include "state/ObjectType.h"
#include "GMap.h"
#include <iostream>

namespace render {

  GRender::GRender():
  window(sf::VideoMode(800, 600), "Until last barrel")
  
  {
    window.setFramerateLimit(60);

  }




    void GRender::display (GState& g){
        window.draw(g.getGMap());

        std::vector<GPlayer> players = g.getGPlayers();
        for(auto player: players){
            window.draw(player);
        }

        // Display the turn count
        int height = 14;

        sf::Text turnCount;

        sf::Font font;

        if (!font.loadFromFile("res/army1.ttf")){
            std::cout << "Font not found" << std::endl;
        }

        turnCount.setFont(font);
        turnCount.setString("Turn number " + std::to_string(g.getTurn()));
        turnCount.setCharacterSize(height); 
        turnCount.setFillColor(sf::Color::White);
        turnCount.setStyle(sf::Text::Bold);
        turnCount.setPosition(10, height * 2);
        window.draw(turnCount);

        window.display();    

    }

};

