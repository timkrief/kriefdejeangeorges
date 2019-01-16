#include "DeepCPU_2.h"
#include "Noeud.h"
#include "state/GameState.h"
#include "engine/GameEngine.h"
#include "engine/CommandEndTurn.h"
#include "engine/CommandMove.h"


#include <cstdlib>
#include <iostream>
#include <ctime>


namespace ai {

bool contains(const std::vector<std::shared_ptr<Noeud> > &list, const std::shared_ptr<Noeud> &elem)
{
    for (int i = 0 ; i < list.size() ; i++)
        if (elem->equal(list.at(i)))
            return true;
    return false;
}

DeepCPU_2::DeepCPU_2 (
        std::shared_ptr<state::GameState> state,
        std::shared_ptr<engine::GameEngine> engine,
        unsigned int playerId
        ) : CPU (state, engine, playerId) {

    int rand = std::rand();

    targetedPlayerId = (playerId+1)% (state->getPlayerCount() );

    completeMap();
}
void DeepCPU_2::run (){
    for (int objCpuCount = 0 ; objCpuCount < state->getPlayer(playerId)->getOwnedFieldObjects().size() ; objCpuCount++)
    {
        std::cout<< "Le nombre d'objet du joueur "<< playerId<< " est "<< state->getPlayer(playerId)->getOwnedFieldObjects().size() << std::endl;
        std::cout << "On sélectionne actuellement l'objet"<< objCpuCount<< std::endl;
        // init the var
        std::vector< std::shared_ptr<Noeud> > bestPath;
        int minSize = state->getMap()->getSize().x * state->getMap()->getSize().y; // on prend un min qui est egal au nombre de case de la map pour être sure d'avoir moins
        int noMove = 0;
        std::vector< std::shared_ptr<Noeud> > newPath;
        for (int playerCount = 0 ; playerCount < state->getPlayerCount() ; playerCount ++)
            if (playerCount != playerId)
                for (int objTargetCount = 0 ; objTargetCount < state->getPlayer(playerCount)->getOwnedFieldObjects().size() ; objTargetCount++ )
                {
                    // init map
                    initMap();
                    std::cout<< "\n";
                    std::cout<< "\n";
                    displayMap();
                    std::cout<< "\n";
                    // chercher le chemin
                    sf::Vector2u cpuPos = state->getPlayer(playerId)->getOwnedFieldObjects().at(objCpuCount)->getPosition();
                    sf::Vector2u targetPos = state->getPlayer(playerCount)->getOwnedFieldObjects().at(objTargetCount)->getPosition();
                    auto origin = getNoeudAt(cpuPos.x, cpuPos.y);
                    auto dest = getNoeudAt(targetPos.x, targetPos.y);
                    std::cout<< "L'unité "<< objCpuCount  << " du joueur: "<< playerId << 
                    " cherche à atteindre l'unité " << objTargetCount<< " du joueur "<<playerCount  <<std::endl;
                    std::cout<< "\n";
                    std::cout<< "On cherche donc à aller depuis "<< cpuPos.x<< "," <<cpuPos.y << " vers "<< targetPos.x<< "," <<targetPos.y  <<std::endl;
                    

                    auto voisins = getNeighboursOf(dest); // vue que la case est innacessible on cherche a atteindre ses voisins
                    
                    for (int i = 0 ; i < voisins.size() ; i++)
                    {
                        if(origin == voisins.at(i)){
                            noMove=1;
                            break;
                        }
                        else
                        {                        
                           newPath = getPathFromTo ( origin, voisins.at(i) );
                        }
                        
                        // regarder si le cout du chemin est inferieur au cout minimal
                        if (minSize > newPath.back()->getCout()){
                            minSize = newPath.back()->getCout();
                            bestPath = newPath;
                        }
                    }
                }
        // move
        if (noMove !=1){
            int diffX = bestPath.at(0)->getX() - state->getPlayer(playerId)->getOwnedFieldObjects()[objCpuCount]->getPosition().x ;
            int diffY = bestPath.at(0)->getY() - state->getPlayer(playerId)->getOwnedFieldObjects()[objCpuCount]->getPosition().y ;
            move(diffX,diffY,objCpuCount);
            for (int i = 0; i<(bestPath.size()-1); i++)
            {
                if (state->getPlayer(playerId)->getOwnedFieldObjects()[objCpuCount]->getMovePoints() >= bestPath.at(i+1)->getValue() )
                {
                    //Test to know if there still enough move point to make a legal move
                    diffX = bestPath.at(i+1)->getX() - bestPath.at(i)->getX();
                    diffY = bestPath.at(i+1)->getY() - bestPath.at(i)->getY();
                    move(diffX,diffY, objCpuCount);
                }
            }
        }    
    }
    engine->addCommand(std::make_shared<engine::CommandEndTurn>(playerId));
}

void DeepCPU_2::move(int diffX, int diffY, int objMoving)
{
    int dir;
    if (diffX>0)
    {
        dir = 1;    
        std::cout<<"L'unité " <<objMoving << " effectue un mouvement vers la droite " <<std::endl;
    
    
    }
    else if (diffX<0)
    {
        dir = 3;
        std::cout<<"L'unité " <<objMoving << " effectue un mouvement vers la gauche " <<std::endl;
    
    }

    if (diffY>0)
    {
        dir = 2;
        std::cout<<"L'unité " <<objMoving << " effectue un mouvement vers le bas " <<std::endl;
    
    }
    else if (diffY<0)
    {
        dir = 0;
        std::cout<<"L'unité " <<objMoving << " effectue un mouvement vers le haut " <<std::endl;
    }
    engine->addCommand(std::make_shared<engine::CommandMove>(dir, objMoving,playerId));
}

void DeepCPU_2::displayMap()
{
    int value;
    int previousX = 0;

    for (int i = 0; i<(m_listNoeud.size()-1); i++)
    {
        value = m_listNoeud.at(i)->getValue();
        if (value<10 && value>0)
        {
            std::cout<< "0"<<value;
        }
        else if(value ==0 )
        {
            std::cout<<"--";

        }
        else
        {
            std::cout<< value;
        }
        std::cout<< "  ";
        if (previousX +1 == m_listNoeud.at(i)->getX())
        {
            std::cout<< "\n";


        }


        

        previousX = m_listNoeud.at(i)->getX();
    }
    return;
    
}

void DeepCPU_2::completeMap()
{   
    sf::Vector2u mapSize = state->getMap()->getSize();
    for (int i = 0 ; i < mapSize.x ; i++)
        for (int j = 0 ; j < mapSize.y ; j++)
        {
            sf::Vector2u position;
            int moveValue;
            position.x = i;
            position.y = j;
            moveValue = state->getMap()->getTile(position)->attributes["moveCost"];
            m_listNoeudRaw.push_back(std::shared_ptr<Noeud>(new Noeud(moveValue,i,j)));
        }
}

void DeepCPU_2::initMap()
{
    m_listNoeud.clear();
    for(int i = 0 ; i < m_listNoeudRaw.size() ; i++)
        if ( m_listNoeudRaw.at(i)->getValue() <0)
        {
            
            m_listNoeud.push_back(std::shared_ptr<Noeud>(new Noeud(0,
                                                                m_listNoeudRaw.at(i)->getX(),
                                                                m_listNoeudRaw.at(i)->getY())));
        }
        else
        {
            m_listNoeud.push_back(std::shared_ptr<Noeud>(new Noeud(m_listNoeudRaw.at(i)->getValue(),
                                                                    m_listNoeudRaw.at(i)->getX(),
                                                                    m_listNoeudRaw.at(i)->getY())));
        }

    for (int i = 0 ; i < state->getPlayerCount() ; i ++)
        for (int j = 0 ; j < state->getPlayer(i)->getOwnedFieldObjects().size() ; j++ )
            getNoeudAt(state->getPlayer(i)->getOwnedFieldObjects().at(j)->getPosition().x,state->getPlayer(i)->getOwnedFieldObjects().at(j)->getPosition().y)->setValue(0);//On remplace le poids des Noeuds occupés par -1
}

const std::shared_ptr<Noeud> &DeepCPU_2::getNoeudAt(int x, int y) const
{
    for (int i = 0; i < m_listNoeud.size() ; i++){
        if (m_listNoeud.at(i)->getX() == x && m_listNoeud.at(i)->getY() == y)
            return m_listNoeud.at(i);
    }
    return std::shared_ptr<Noeud>(nullptr);
}
void DeepCPU_2::clearMap()
{
    for (int i = 0; i < m_listNoeud.size() ; i++)
        m_listNoeud.at(i)->clear();
}

const std::vector< std::shared_ptr<Noeud> > DeepCPU_2::getPathFromTo(const std::shared_ptr<Noeud> &origin,
                                                                     const std::shared_ptr<Noeud> &destination)
{
    std::vector<std::shared_ptr<Noeud> > closedList;
    std::vector<std::shared_ptr<Noeud> > openList;

    openList.push_back(origin);

    while (!openList.empty()){
        std::shared_ptr<Noeud> u = openList.at(noeudPrioritaire(openList));

        for (int i = 0 ; i < openList.size() ; i++)
            if (openList.at(i)->equal(u)){
                openList.erase(openList.begin() + i);
                break;
            }
        if (u->getValue() > 0 || u->equal(origin)){ // need to add the origin condition cause as their is smth on the first case, his value is 0
            auto neighbours = getNeighboursOf(u);

            for (int i = 0 ; i < neighbours.size() ; i++)
                if (neighbours.at(i)->getValue() > 0)
                {
                    int newCost = u->getCout()+neighbours.at(i)->getValue();
                    if (contains(openList,neighbours.at(i))  &&  neighbours.at(i)->getCout() <= newCost){
                    } else if (contains(closedList,neighbours.at(i)) &&  neighbours.at(i)->getCout() <= newCost){
                    } else {
                        neighbours.at(i)->setCout(newCost);
                        neighbours.at(i)->setHeuristique(neighbours.at(i)->getCout() + abs(neighbours.at(i)->getX()-destination->getX()) + abs(neighbours.at(i)->getY()-destination->getY()));
                        openList.push_back(neighbours.at(i));
                    }
                }
            closedList.push_back(u);
        }
    }
    // now extract path (maybe split here to make two functions)
    std::vector<std::shared_ptr<Noeud> > truePath;
    truePath.push_back(destination);
    for ( int i = closedList.size() - 1 ; i >= 0 ; i--)
        if (!contains(truePath, closedList.at(i))){
            std::shared_ptr<Noeud> newCase = bestCaseNear(truePath.at(0));
            if (newCase)
                truePath.insert(truePath.begin(), newCase);
        }
    return truePath;
}


int DeepCPU_2::noeudPrioritaire(const std::vector< std::shared_ptr<Noeud> > &list) const
{
    int i = 0;
    int min = list.at(i)->getHeuristique();
    int indexelementmin = 0;
    for (int i = 1 ; i < list.size() ; i++)
        if (min > list.at(i)->getHeuristique()){
            min = list.at(i)->getHeuristique();
            indexelementmin = i;
        }
    return indexelementmin;
}

const std::shared_ptr<Noeud> DeepCPU_2::bestCaseNear(const std::shared_ptr<Noeud> &noeud) const
{
    for(int i = 0 ; i < m_listNoeud.size() ; i++)
        if (m_listNoeud.at(i))
            if (m_listNoeud.at(i)->isAssigned() &&
                    m_listNoeud.at(i)->getCout() == noeud->getCout() -  noeud->getValue() &&
                    noeud->isNeighbourOf(m_listNoeud.at(i)))
            {
                return m_listNoeud.at(i);
            }
    return std::shared_ptr<Noeud>(nullptr);
}

std::vector< std::shared_ptr<Noeud> > DeepCPU_2::getNeighboursOf(const std::shared_ptr<Noeud> &noeud) const
{
    std::vector< std::shared_ptr<Noeud> > voisins;
    for (int i = 0 ; i < m_listNoeud.size() ; i++)
        if ( m_listNoeud.at(i)->isNeighbourOf(noeud) && !m_listNoeud.at(i)->equal(noeud))
            voisins.push_back(m_listNoeud.at(i));
    return voisins;
}

}



