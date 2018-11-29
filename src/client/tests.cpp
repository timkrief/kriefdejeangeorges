#include "tests.h"

#include <SFML/Graphics.hpp>
#include <iostream>


void testSFML() {
    sf::Texture texture;
}


void testPlayer() {
	cout << "Test of the static counter of the Player class:" << endl;
	Player player;
	cout << "Player n°" << player.getId() << endl;
	Player player2;
	cout << "Player n°" << player2.getId() << endl << endl;
	cout << "Test of Player's money getters and setters (oil ones are similar):" << endl;
	cout << "Setting player's money to -5 (no negative value allowed)" << endl;
	player.setMoney(-5.f);
	cout << "Player's money: " << player.getMoney() << endl << endl;
	cout << "Setting player's money to 3.6 (expecting to return only int)" << endl;
	player.setMoney(3.6f);
	cout << "Player's money: " << player.getMoney() << endl << endl;
}

int testRender(GameState& state){
    GRender my_render;
    
    sf::RenderWindow& renderWindow = my_render.window;
    auto sharedState= std::make_shared<GameState>(state);
    render::GState gstate(sharedState);
    
    bool displayWindow = true;
    sf::Event event;
    
     while(displayWindow){
        while (renderWindow.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                displayWindow = false;
            }
        }

        renderWindow.clear();
        my_render.display(gstate);
    }
    return 0;
}



int testMapLoaded(Map map) { // rendererPrototype
    int width = 800;
    int height = 600;
    sf::RenderWindow window(sf::VideoMode(width, height), "Test of the map");
    window.setFramerateLimit(60);

    bool displayWindow = true;
    sf::Event event;

    while(displayWindow){
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                displayWindow = false;
            }
        }
        window.clear();
        
        sf::Texture texture;
        Tileset tileset = map.getTileset();
        texture.loadFromFile(tileset.getResourcePath());
        
        sf::Sprite sprite;
        sprite.setTexture(texture);
        
        for(unsigned int x = 0; x < map.getSize().x; x++){
            for(unsigned int y = 0; y < map.getSize().y; y++){
                //float speed = map.getTile(sf::Vector2u(x,y))->getSpeed();
                
                unsigned int tileId = map.getData(sf::Vector2u(x,y));
                
                sprite.setTextureRect(tileset.getTileIntRect(tileId));
                
                //sprite.setSize(sf::Vector2f((float)width / (float)map.getSize().x, (float)height / (float)map.getSize().y));
                sprite.setPosition(x * tileset.getTileSize().x, y * tileset.getTileSize().y);
                
                //int luminosity = speed * 255.f;
                //sprite.setColor(sf::Color(luminosity, luminosity, luminosity));

                window.draw(sprite);
            }
        }
        
        window.display();
    }

    window.close();
    
    return 0;
}

void testEngine(std::shared_ptr<GameState> state){
    GameEngine engine(state);
    
    for(int i=0; i<10; i++){
         engine.addCommand(make_shared<CommandEndTurn>());
    }
    
    engine.update();
}
