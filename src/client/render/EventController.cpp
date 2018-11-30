#include "EventController.h"
#include "engine/GameEngine.h"
#include "engine/CommandEndTurn.h"
#include "engine/CommandMove.h"

#include <iostream>

namespace render {
    EventController::EventController() :
        shiftPressed(false),
        controlPressed(false),
        altPressed(false){
        
    }
    
    void EventController::handle (sf::Event& event, std::shared_ptr<engine::GameEngine> engine, sf::RenderWindow& window, bool& displayWindow){
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
                        engine->addCommand(std::make_shared<engine::CommandMove>(0, 0));
                        break;  
                    case sf::Keyboard::Right:
                        engine->addCommand(std::make_shared<engine::CommandMove>(1, 0));
                        break;  
                    case sf::Keyboard::Down:
                        engine->addCommand(std::make_shared<engine::CommandMove>(2, 0));
                        break;  
                    case sf::Keyboard::Left:
                        engine->addCommand(std::make_shared<engine::CommandMove>(3, 0));
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
                sf::View view{ window.getView() };
                view.setSize(event.size.width, event.size.height);
                window.setView(view);
                break; }
            case sf::Event::MouseWheelScrolled: {
                if(controlPressed){
                    float zoomAmount = 1.05f;
                    if (event.mouseWheelScroll.delta > 0){
                        zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, window, (1.f / zoomAmount));
                    } else if (event.mouseWheelScroll.delta < 0) {
                        zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, window, zoomAmount);
                    }
                } else {
                    float sensibility = 5.f;
                    sf::Vector2f move;
                    if(shiftPressed || event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel) {
                        move.x -= event.mouseWheelScroll.delta * sensibility;
                    } else {
                        move.y -= event.mouseWheelScroll.delta * sensibility;
                    }
                    
                    sf::View view{ window.getView() };
                    view.move(move);
                    window.setView(view);
                }
                break; }
            default:
                break;
        }
    }
    
    // function found here: https://github.com/SFML/SFML/wiki/Source:-Zoom-View-At-(specified-pixel)
    void EventController::zoomViewAt(sf::Vector2i pixel, sf::RenderWindow& window, float zoom){
	    const sf::Vector2f beforeCoord{ window.mapPixelToCoords(pixel) };
	    sf::View view{ window.getView() };
	    view.zoom(zoom);
	    window.setView(view);
	    const sf::Vector2f afterCoord{ window.mapPixelToCoords(pixel) };
	    const sf::Vector2f offsetCoords{ beforeCoord - afterCoord };
	    view.move(offsetCoords);
	    window.setView(view);
    }
};

