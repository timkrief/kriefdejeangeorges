#include "Cursor.h"
#include <SFML/Graphics.hpp>
#include <math.h> 
#include <sys/time.h>

namespace render {

    Cursor::Cursor (unsigned int size, sf::Vector2u position):
    	size(size),
    	position(position),
    	color(sf::Color::White) {
    
    }
    Cursor::Cursor (unsigned int size, sf::Vector2u position, sf::Color color):
    	size(size),
    	position(position),
    	color(color) {
    
    }
    void Cursor::draw (sf::RenderTarget& target, sf::RenderStates states) const{
    
        struct timeval tp;
        gettimeofday(&tp, NULL);
        int time = (tp.tv_sec * 1000 + tp.tv_usec / 1000) % 86400000;
        
        // Display cursor
        sf::RectangleShape rect(sf::Vector2f(size,size));
        rect.setPosition(sf::Vector2f(position) * (float)size);
        rect.setOutlineThickness(1.f);
        rect.setFillColor( sf::Color(color.r, color.g, color.b, 16 + 32 * (1 + sin(time / 100) )/2 ) );
        rect.setOutlineColor( sf::Color(color.r, color.g, color.b, 100) );
        target.draw(rect);        
    }

};
