
#include "GRender.h"
#include <SFML/Graphics.hpp>
#include "GState.h"
#include "state/GameState.h"
#include "state/ObjectType.h"
#include "TextureManager.h"
#include "GMap.h"
#include <iostream>
#include <math.h> 
#include <chrono> 

namespace render {

    GRender::GRender():
        window(std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "Until the last barrel")),
        cursor(sf::Vector2u(0, 0)),
        cameraZoom(sf::Vector2f(1.f, 1.f))
    {
        window->setFramerateLimit(60);
    }

    void GRender::initTextures(){
        TextureManager::loadTexture("mapTexture", "./res/sprites/mapTileset.png");
        TextureManager::loadTexture("buildings", "./res/sprites/buildings.png");
        TextureManager::loadTexture("units", "./res/sprites/units.png");
    }
    
    std::shared_ptr<sf::RenderWindow> GRender::getWindow(){
        return window;
    }
    
    void GRender::setCursor(sf::Vector2u newCursor){
        cursor = newCursor;
    }
    
    void GRender::display (GState& g){
    
        sf::View view = window->getView();
        
        view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
        window->setView(view);
        
        
        auto time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    
        window->clear(sf::Color(44, 146, 206));
        
        window->draw(g.getGMap());

        std::vector<GPlayer> players = g.getGPlayers();
        for(auto player: players){
            window->draw(player);
        }
        
        sf::RectangleShape rect(sf::Vector2f(16,16));
        rect.setPosition(sf::Vector2f(cursor) * 16.f);
        rect.setOutlineThickness(1.f);
        rect.setFillColor( sf::Color(255,255,255, 16 + 32 * (1 + sin(time / 100) )/2 ) );
        rect.setOutlineColor( sf::Color(255,255,255,100) );
        window->draw(rect);        
        

        
        // Minimap
        /*
        auto view2 = view;
        view2.setViewport(sf::FloatRect(0.7f, 0.05f, 0.25f, 0.25f));
        view2.zoom(4);
        window->setView(view2);
        window->draw(g.getGMap());
        */

        sf::View gui({window->getSize().x/2, window->getSize().y/2}, sf::Vector2f(window->getSize()));
        
        window->setView(gui);
        
        // Display the turn count
        int height = 14;

        sf::Text turnCount;

        sf::Font font;

        if (!font.loadFromFile("res/army1.ttf")){
            std::cout << "Font not found" << std::endl;
        }

        turnCount.setFont(font);
        turnCount.setString("Turn number " + std::to_string(g.getTurn()/g.getPlayerCount()));
        turnCount.setCharacterSize(height); 
        //turnCount.setFillColor(sf::Color::White);
        turnCount.setStyle(sf::Text::Bold);
        turnCount.setPosition(10, height * 2);
        window->draw(turnCount);
        
        window->setView(view);
        
        window->display();    
    }

    
    sf::Vector2f GRender::getCameraPosition(){
        return cameraPosition;
    }
    void GRender::updateCameraPosition(sf::Vector2f position){
        cameraPosition = cameraPosition + position / getCameraZoom().x;
    }
    sf::Vector2f GRender::getCameraZoom(){
        return cameraZoom;
    }
    void GRender::updateCameraZoom(sf::Vector2f zoom){
        cameraZoom = {cameraZoom.x / zoom.x, cameraZoom.y / zoom.y};
    }
};

