#include "EventController.h"
#include "engine/GameEngine.h"
#include "engine/CommandEndTurn.h"
#include "engine/CommandMove.h"

namespace render {
    EventController::EventController(){
        
    }
    
    void EventController::handle (sf::Event& event, engine::GameEngine& engine, sf::RenderWindow& window, bool& displayWindow){
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
                        engine.addCommand(std::make_shared<engine::CommandEndTurn>());
                        break;  
                    case sf::Keyboard::Up:
                        engine.addCommand(std::make_shared<engine::CommandMove>(0));
                        break;  
                    case sf::Keyboard::Right:
                        engine.addCommand(std::make_shared<engine::CommandMove>(1));
                        break;  
                    case sf::Keyboard::Down:
                        engine.addCommand(std::make_shared<engine::CommandMove>(2));
                        break;  
                    case sf::Keyboard::Left:
                        engine.addCommand(std::make_shared<engine::CommandMove>(3));
                        break;  
                    default:
                        break;
                }
                break;
            case sf::Event::Resized:
                window.setSize(sf::Vector2u(event.size.width, event.size.height));
                break;
            default:
                break;
        }
    }
};

