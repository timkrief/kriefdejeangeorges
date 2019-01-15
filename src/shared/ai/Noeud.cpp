#include "Noeud.h"
#include "state/GameState.h"
#include "engine/GameEngine.h"
#include "engine/CommandEndTurn.h"
#include "engine/CommandMove.h"


#include <cstdlib>
#include <iostream>
#include <ctime>
#include <unistd.h>
#include <set>
#include <sstream> 
#include <string> 


namespace ai {
    

     /*------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*Methodes et constructeur*/
    Noeud::Noeud(int value, int x, int y):
        m_value(value), m_x(x), m_y(y), m_cout(0), m_heuristique(0), m_isAssign(false)
    {

    }

    int Noeud::getValue() const
    {
        return m_value;
    }

    int Noeud::getX() const
    {
        return m_x;
    }
    int Noeud::getY() const
    {
        return m_y;
    }
        
    int Noeud::getCout() const
    {
        return m_cout;
    }

    int Noeud::getHeuristique() const
    {
        return m_heuristique;
    }
        
    void Noeud::setCout(int cout)
    {
        m_cout = cout;
        m_isAssign = true;
    }

    void Noeud::setHeuristique(int heuristique)
    {
        // if condition
        m_heuristique = heuristique;
        m_isAssign = true;
    }

    bool Noeud::isAssigned() const
    {
        return m_isAssign;
    }

    void Noeud::clear()
    {
        m_isAssign = false;
        m_heuristique = 0;
        m_cout = 0;
    }
        
    bool Noeud::isNeighbourOf(const std::shared_ptr<Noeud> noeud) const
    {
        int diffX = m_x - noeud->getX();
        int diffY = m_y - noeud->getY();
        if ( (diffX == 1 || diffX == -1 ) && diffY == 0)
            return true;
        if ( (diffY == 1 || diffY == -1 ) && diffX == 0)
            return true;
        return false;
    }

    int Noeud::compareWith(const std::shared_ptr<Noeud> noeud) const
    {
        if (m_heuristique < noeud->getHeuristique())
            return 1;
        if (m_heuristique == noeud->getHeuristique())
            return 0;
        return -1;
    }
}
