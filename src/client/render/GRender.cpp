
#include "GRender.h"
#include <SFML/Graphics.hpp>
#include "GState.h"
#include "state/GameState.h"
#include "state/ObjectType.h"
#include "TextureManager.h"
#include "GMap.h"
#include <iostream>
#include <math.h> 
#include <sys/time.h>
#include "Cursor.h"

namespace render {

    sf::Font GRender::armyFont;
    sf::Font GRender::vcrFont;
        
    GRender::GRender():
        window(std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "Until the last barrel")),
        cursor(sf::Vector2u(0, 0)),
        selectedTile(sf::Vector2u(0, 0)),
        selectedPlayer(-1),
        selectedFieldObject(-1),
        cameraZoom(sf::Vector2f(1.f, 1.f)),
        uiScale(1.f),
        newSelection(true)
    {
        window->setFramerateLimit(60);
        
        if (!GRender::armyFont.loadFromFile("./res/font/army1.ttf")){
            std::cout << "Army1 font not found" << std::endl;
        }

        if (!GRender::vcrFont.loadFromFile("./res/font/VCR_OSD_MONO.ttf")){
            std::cout << "VCR OSD MONO font not found" << std::endl;
        }
    }

    void GRender::initTextures(){
        TextureManager::loadTexture("mapTexture", "./res/sprites/mapTileset.png");
        TextureManager::loadTexture("buildings", "./res/sprites/buildings.png");
        TextureManager::loadTexture("units", "./res/sprites/units.png");
        TextureManager::loadTexture("vignette", "./res/vignette.png");
        TextureManager::loadTexture("lightEffect", "./res/lightEffect.png");
        TextureManager::loadTexture("planet", "./res/planet.png");
        TextureManager::loadTexture("sky", "./res/sky.png");
        TextureManager::loadTexture("moon", "./res/moon.png");
    }
    
    std::shared_ptr<sf::RenderWindow> GRender::getWindow(){
        return window;
    }
    
    void GRender::setCursor(sf::Vector2u newCursor){
        cursor = newCursor;
    }
    
    sf::Vector2u GRender::getCursor(){
        return cursor;
    }
    
    
    void GRender::display (GState& g){
    
	    sf::View view = window->getView();
	    
	    view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
	    window->setView(view);
	    
	    // Time
	    struct timeval tp;
	    gettimeofday(&tp, NULL);
	    int time = (tp.tv_sec * 1000 + tp.tv_usec / 1000) % 86400000;
		
		
        sf::Vector2f absPosition = sf::Vector2f((view.getCenter().x - 400) * cameraZoom.x, (view.getCenter().y-300) * cameraZoom.y);
        // TODO: 400 and 300 must be replaced dynamicaly with half the size of the map
        
        double squareDistance = 
        	(view.getCenter().x - 400) * (view.getCenter().x - 400) + 
        	(view.getCenter().y - 300) * (view.getCenter().y - 300);
        
		float absDistance = (cos(
			std::min(
				(
					absPosition.x * absPosition.x + 
					absPosition.y * absPosition.y
				)/(1000.f*1000.f*2.f),
				1.f
			) * 3.1416f
		) + 1.f)/2.f;
		
		int maxWindowEdge = std::max(window->getSize().x, window->getSize().y); 
		
    	if(cameraZoom.x > 0.013f && squareDistance < maxWindowEdge * maxWindowEdge / cameraZoom.x / cameraZoom.x){
		    
		    window->clear(sf::Color(44, 146, 206));
		    window->draw(g.getGMap());
			
		    std::vector<GPlayer> players = g.getGPlayers();
		    
		    if(newSelection){
				selectedPlayer = -1;
				selectedFieldObject = -1;
				
				for(auto player: players){
					player.getSelection(selectedTile, selectedPlayer, selectedFieldObject, selectedUnit);
					selectedPlayer;
					if(selectedFieldObject>=0){
		    			newSelection = false;
						break;
					}
				}
		    } else {
		    	selectedTile = players[selectedPlayer].getSelectionPosition(selectedFieldObject);
		    }
		    
		    for(auto player: players){
		        window->draw(player);
		    }
		    
		    // Display cursor
		    Cursor gCursor(16, cursor);
		    window->draw(gCursor);
		    // Display selectedTileCursor
		    if(selectedFieldObject>=0){
				Cursor gSelectedTile(16, selectedTile, sf::Color::Black);
				window->draw(gSelectedTile);
		    }
    	} else {
		    window->clear(sf::Color(15,22,28));
		    
		    sf::Vector2u skySize = TextureManager::getTexture("sky")->getSize();
		    sf::Sprite skySprite(*(TextureManager::getTexture("sky")), sf::IntRect(0, 0, skySize.x, skySize.y));
			skySprite.setOrigin(skySize.x/2, skySize.y/2);
			skySprite.setColor(sf::Color(255,255,255,200));
			float skyZoom = 1.41*
				maxWindowEdge/
				std::min(skySize.x, skySize.y);
			skySprite.setScale(skyZoom/cameraZoom.x, skyZoom/cameraZoom.y);
			skySprite.setPosition(view.getCenter().x, view.getCenter().y);
			skySprite.setRotation(time/2000.f);
        	window->draw(skySprite);
        	
		    sf::Vector2u moonSize = TextureManager::getTexture("moon")->getSize();
		    sf::Sprite moonSprite(*(TextureManager::getTexture("moon")), sf::IntRect(0, 0, moonSize.x, moonSize.y));
			moonSprite.setOrigin(moonSize.x/2, moonSize.y/2);
			
        	/*
			moonSprite.setScale(1200, 1200);
			moonSprite.setPosition(-700000 + view.getCenter().x*.5, -300000 + view.getCenter().y*.5);
        	window->draw(moonSprite);
        	*/
		    sf::Vector2u planetSize = TextureManager::getTexture("planet")->getSize();
		    sf::Sprite planetSprite(*(TextureManager::getTexture("planet")), sf::IntRect(0, 0, planetSize.x, planetSize.y));
			planetSprite.setOrigin(planetSize.x/2, planetSize.y/2);
			planetSprite.setScale(1200, 1200);
        	window->draw(planetSprite);
        
			moonSprite.setScale(20000, 20000);
			moonSprite.setPosition(-(view.getCenter().x-400) * cameraZoom.x * 100000 , 12000000 + -(view.getCenter().y-300) * cameraZoom.y * 100000);
        	window->draw(moonSprite);
		}
		    
        
        

        sf::View gui({window->getSize().x/2, window->getSize().y/2}, sf::Vector2f(window->getSize()));
        
        window->setView(gui);
        
        
        
		auto angle = 	atan2(absPosition.x + 1500, absPosition.y + 1500 ) + 
						atan2(absPosition.x - 2500, absPosition.y - 2500 );
		
		
		float intensity = ((sin(angle*50)+1.f)*80+70)*absDistance;
		
        sf::IntRect vignette(0, 0, 1920, 1080);
        sf::Sprite vignetteSprite(*(TextureManager::getTexture("vignette")), vignette);
		vignetteSprite.setOrigin(0, 0);
		vignetteSprite.setScale(
    		window->getSize().x / 1920.f, 
    		window->getSize().y / 1080.f);
		vignetteSprite.setColor(sf::Color(0, 0, 0, 230-intensity));
        vignetteSprite.setPosition(0, 0);
        window->draw(vignetteSprite);
        
        ////std::cout << distance << std::endl;
        
        sf::Vector2u lightEffectSize = TextureManager::getTexture("lightEffect")->getSize();
        sf::IntRect lightEffect(0, 0, lightEffectSize.x, lightEffectSize.y);
        sf::Sprite lightEffectSprite(*(TextureManager::getTexture("lightEffect")), lightEffect);
		lightEffectSprite.setOrigin(lightEffectSize.x/2, lightEffectSize.y/2);
        lightEffectSprite.setPosition(window->getSize().x/2, window->getSize().y/2);
        float lightEffectZoomRatio = std::max(window->getSize().x, window->getSize().y) / (float)lightEffectSize.x * 1.4f;
		lightEffectSprite.setScale(lightEffectZoomRatio, lightEffectZoomRatio);
		
		
        lightEffectSprite.setRotation(angle*180/3.1416f*20);
		lightEffectSprite.setColor(sf::Color(255, 255, 255, intensity));
        
        window->draw(lightEffectSprite);
        
        
        // Display the turn count
        int height = 16 * uiScale;
        sf::Text turnCount;
        turnCount.setFont(armyFont);
        turnCount.setString("Turn " + std::to_string(g.getTurn()/g.getPlayerCount()));
        turnCount.setCharacterSize(height);
        turnCount.setStyle(sf::Text::Bold);
        turnCount.setPosition(height, height);
        
        sf::Vector2f guiTopLeftPanelSize(turnCount.getLocalBounds().width + height*2, height*4);
        sf::RectangleShape guiTopLeftPanel(guiTopLeftPanelSize);
        guiTopLeftPanel.setFillColor(sf::Color(0,0,0,126));
        window->draw(guiTopLeftPanel);
        window->draw(turnCount);
        
        
        
        
        
        // draw tile info overlay
        sf::Vector2f guiBottomRightPanelSize(200 * uiScale, 250 * uiScale);
        float guiFontSize = 18;
        
        sf::RectangleShape guiBottomRightPanel(guiBottomRightPanelSize);
        guiBottomRightPanel.setPosition(gui.getSize() - guiBottomRightPanelSize);
        guiBottomRightPanel.setFillColor(sf::Color(0,0,0,126));
        window->draw(guiBottomRightPanel);
        
        
        sf::Sprite hovered(g.getGMap().getTile(cursor));
        hovered.setScale(10*uiScale,10*uiScale);
        sf::FloatRect hoveredRect(hovered.getGlobalBounds());
        hovered.setPosition(guiBottomRightPanel.getPosition() + (sf::Vector2f(guiBottomRightPanelSize.x, guiBottomRightPanelSize.x) - sf::Vector2f(hoveredRect.width, hoveredRect.height))/2.f);
        window->draw(hovered);
        
        sf::Text cursorTileDescription;
        cursorTileDescription.setFont(vcrFont);
        cursorTileDescription.setCharacterSize(guiFontSize * uiScale);
        cursorTileDescription.setString("Move cost " + g.getGMap().getTileDescription(cursor, "moveCost"));
        
        cursorTileDescription.setPosition(
            guiBottomRightPanel.getPosition() +
            sf::Vector2f(guiBottomRightPanelSize.x / 2.f, guiBottomRightPanelSize.x) +
            sf::Vector2f(-cursorTileDescription.getLocalBounds().width / 2.f, guiFontSize * 0 * uiScale)
        );
        window->draw(cursorTileDescription);
        
        cursorTileDescription.setString("Defense bonus " + g.getGMap().getTileDescription(cursor, "defense"));
        cursorTileDescription.setPosition(
            guiBottomRightPanel.getPosition() +
            sf::Vector2f(guiBottomRightPanelSize.x / 2.f, guiBottomRightPanelSize.x) +
            sf::Vector2f(-cursorTileDescription.getLocalBounds().width / 2.f, guiFontSize * 1 * uiScale)
        );
        window->draw(cursorTileDescription);
        
        
        
        
        if(selectedFieldObject>=0){
		    // draw unit info overlay
		    sf::RectangleShape guiBottomLeftPanel(guiBottomRightPanelSize);
		    guiBottomLeftPanel.setPosition(sf::Vector2f(0.f, gui.getSize().y - guiBottomRightPanelSize.y));
		    guiBottomLeftPanel.setFillColor(sf::Color(0,0,0,126));
		    window->draw(guiBottomLeftPanel);
		    
		    selectedUnit.setScale(10 * uiScale);
		    selectedUnit.setPosition(sf::Vector2i(guiBottomLeftPanel.getPosition() + (sf::Vector2f(guiBottomRightPanelSize.x, guiBottomRightPanelSize.x) - sf::Vector2f(hoveredRect.width, hoveredRect.height))/2.f));
		    window->draw(selectedUnit);
		    
		    cursorTileDescription.setFont(vcrFont);
		    cursorTileDescription.setCharacterSize(guiFontSize * uiScale);
		    cursorTileDescription.setString("Move points " + std::to_string(selectedUnit.getMovePoints()) + "/"+ std::to_string(selectedUnit.getNormalMovePoints()));
		    
		    cursorTileDescription.setPosition(
		        guiBottomLeftPanel.getPosition() +
		        sf::Vector2f(guiBottomRightPanelSize.x / 2.f, guiBottomRightPanelSize.x) +
		        sf::Vector2f(-cursorTileDescription.getLocalBounds().width / 2.f, guiFontSize * 0 * uiScale)
		    );
		    window->draw(cursorTileDescription);
		    
		}
        
        
        
        
        
        
        
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
    
    void GRender::updateUiScale(float newUiScale){
        uiScale /= newUiScale;
    }
    
    float GRender::getUiScale(){
        return uiScale;
    }
    
    void GRender::selectTile(){
        selectedTile = cursor;
        newSelection = true;
    }
    int GRender::getSelectedPlayer(){
    	return selectedPlayer;
    }
    int GRender::getSelectedFieldObject(){
    	return selectedFieldObject;
    }
};

