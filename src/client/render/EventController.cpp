#include "EventController.h"
#include "engine/GameEngine.h"
#include "engine/CommandEndTurn.h"
#include "engine/CommandMove.h"

#include <iostream>

namespace render {
    EventController::EventController() :
        shiftPressed(false),
        controlPressed(false),
        altPressed(false),
        dragPressed(false),
        middleDragPressed(false),
        mousePosition(sf::Vector2f(0,0)){
    }
    
    void EventController::handle (sf::Event& event, std::shared_ptr<engine::GameEngine> engine, std::shared_ptr<GRender> render, bool& displayWindow){
    
        std::shared_ptr<sf::RenderWindow> window = render->getWindow();
        
        while (window->pollEvent(event)){
            
            switch (event.type){
                // fenêtre fermée
                case sf::Event::Closed:
                    displayWindow = false;
                    break;

                // touche pressée
                case sf::Event::KeyPressed:
                    switch(event.key.code){
                        case sf::Keyboard::Escape:
                            displayWindow = false;
                            break;  
                        case sf::Keyboard::Return:
                            engine->addCommand(std::make_shared<engine::CommandEndTurn>(0));
                            break;  
                        case sf::Keyboard::Up:
                        	if(render->getSelectedPlayer() == 0)
                            	engine->addCommand(std::make_shared<engine::CommandMove>(0, render->getSelectedFieldObject(), 0));
                            break;  
                        case sf::Keyboard::Right:
                        	if(render->getSelectedPlayer() == 0)
                            	engine->addCommand(std::make_shared<engine::CommandMove>(1, render->getSelectedFieldObject(), 0));
                            break;  
                        case sf::Keyboard::Down:
                        	if(render->getSelectedPlayer() == 0)
                            	engine->addCommand(std::make_shared<engine::CommandMove>(2, render->getSelectedFieldObject(), 0));
                            break;  
                        case sf::Keyboard::Left:
                        	if(render->getSelectedPlayer() == 0)
                            	engine->addCommand(std::make_shared<engine::CommandMove>(3, render->getSelectedFieldObject(), 0));
                            break;  
                        case sf::Keyboard::Delete:
                            engine->cancelTurn();
                            break;
                        case sf::Keyboard::Z:
                            if(controlPressed){
                                engine->cancelFromPlayer(0);
                            }
                            break;
                        case sf::Keyboard::S:
                            if(controlPressed){
                                engine->saveHistory();
                            }
                            break;
                        case sf::Keyboard::LShift:
                            shiftPressed = true;
                            break;
                        case sf::Keyboard::LControl:
                            controlPressed = true;
                            break;
                        case sf::Keyboard::LAlt:
                            altPressed = true;
                            break;
                        default:
                            break;
                    }
                    break;
                
                case sf::Event::KeyReleased:
                    switch(event.key.code){
                        case sf::Keyboard::LShift:
                            shiftPressed = false;
                            break;
                        case sf::Keyboard::LControl:
                            controlPressed = false;
                            break;
                        case sf::Keyboard::LAlt:
                            altPressed = false;
                            break;
                        default:
                            break;
                    }
                    break;
                case sf::Event::Resized: {
                    sf::View view{ window->getView() };
                    view.setSize(event.size.width, event.size.height);
                    window->setView(view);
                    break; }
                case sf::Event::MouseWheelScrolled: {
                    
                    float zoomAmount = event.mouseWheelScroll.delta > 0 ? 0.951234f : 1.051234f;
                    if(controlPressed){
                         // function zoomat found here: https://github.com/SFML/SFML/wiki/Source:-Zoom-View-At-(specified-pixel)
                        const sf::Vector2f beforeCoord{ window->mapPixelToCoords({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }) };
                        sf::View view{ window->getView() };
                        view.zoom(zoomAmount);
                        render->updateCameraZoom({zoomAmount, zoomAmount});
                        
                        window->setView(view);
                        const sf::Vector2f afterCoord{ window->mapPixelToCoords({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }) };
                        const sf::Vector2f offsetCoords{ beforeCoord - afterCoord };
                        view.move(offsetCoords);
                        render->updateCameraPosition(offsetCoords);
                        
                        window->setView(view);
	    
                    } else if(altPressed){
                        render->updateUiScale(zoomAmount);
                    } else {
                        float sensibility = 5.1234f;
                        sf::Vector2f move;
                        if(shiftPressed || event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel) {
                            move.x -= event.mouseWheelScroll.delta * sensibility;
                        } else {
                            move.y -= event.mouseWheelScroll.delta * sensibility;
                        }
                        
                        sf::View view{ window->getView() };
                        
                        render->updateCameraPosition(move);
                        
                        view.move(move);
                        window->setView(view);
                    }
                    
                    updateCursor({event.mouseWheelScroll.x, event.mouseWheelScroll.y}, render);
                    
                    break; }
                case sf::Event::MouseMoved: 
                    if(dragPressed || middleDragPressed){
                        sf::View view{ window->getView() };
                        
                        view.move(window->mapPixelToCoords(sf::Vector2i(mousePosition)) - window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y)));
                        window->setView(view);
                        
                    }
                    updateCursor({event.mouseMove.x, event.mouseMove.y}, render);
                    mousePosition = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
                    break; 
                case sf::Event::MouseButtonPressed:
                    if(controlPressed && event.mouseButton.button == sf::Mouse::Left){
                        dragPressed = true;
                    } 
                    if(event.mouseButton.button == sf::Mouse::Middle){
                        middleDragPressed = true;
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    if(event.mouseButton.button == sf::Mouse::Left){
                        if(dragPressed){
                            dragPressed = false;
                        } else {
                    		render->selectTile();
                        }
                    }
                    if(event.mouseButton.button == sf::Mouse::Middle){
                        middleDragPressed = false;
                    }
                    
                    break;
                default:
                    break;
            }
        }
    }
    
    void EventController::updateCursor(sf::Vector2i pixel, std::shared_ptr<GRender> render){
        unsigned int tmpX = std::max(0, (int)render->getWindow()->mapPixelToCoords(pixel).x / 16);
        unsigned int tmpY = std::max(0, (int)render->getWindow()->mapPixelToCoords(pixel).y / 16);
        render->setCursor(sf::Vector2u(tmpX, tmpY));
    }
    
    void EventController::zoomViewAt(sf::Vector2i pixel, std::shared_ptr<sf::RenderWindow> window, float zoom){
    }
};

