#include "DeepCPU_2.h"
#include "Noeud.h"
#include "state/GameState.h"
#include "engine/GameEngine.h"
#include "engine/CommandEndTurn.h"
#include "engine/CommandMove.h"


#include <cstdlib>
#include <iostream>
#include <ctime>

template <class T> bool contains(std::vector<T> list, T elem)
{
    for (int i = 0 ; i < list.size() ; i++)
        if (elem == list.at(i))
            return true;
    return false;
}

namespace ai {
DeepCPU_2::DeepCPU_2 (
        std::shared_ptr<state::GameState> state,
        std::shared_ptr<engine::GameEngine> engine,
        unsigned int playerId
        ) : CPU (state, engine, playerId) {

    int rand = std::rand();

    targetedPlayerId = (playerId+1)% (state->getPlayerCount() );
    //std::cout<<"DeepCPU_2: " << targetedPlayerId <<std::endl;

    completeMap();
    //displayMap();
}
void DeepCPU_2::run (){
    
    sf::Vector2u targetPos = state->getPlayer(targetedPlayerId)->getOwnedFieldObjects().at(0)->getPosition();
    sf::Vector2u cpuPos = state->getPlayer(playerId)->getOwnedFieldObjects().at(0)->getPosition();
    
    std::vector< std::shared_ptr<Noeud> > pathOfVector;
    //std::cout<< "\n Le joueur " << playerId << " part de " << cpuPos.x << ";" << cpuPos.y << " pour aller vers "<< targetPos.x << ";" << targetPos.y   <<std::endl;
    
    //m_listNoeud.clear();
    //completeMap();
    //displayMap();
    auto origin = getNoeudAt(cpuPos.x, cpuPos.y);
    auto dest = getNoeudAt(targetPos.x, targetPos.y);
    pathOfVector = getPathFromTo(origin, dest);
  
    /*Traduction du pathOfVector en commande de direction*/
    /*
    Tant que points_de_mouvement_restant >= m_value_Nième_noeud et qu'on est pas en bout de la liste pathOfVector:
        si Nième.x-N+1ième.x !=0:
            direction = Nième.x-N+1ième.y //cela nous donnes la gauche ou la droite. Il faut juste voir la corresspondance avec les commandes
            on diminue les points de mouvement restant du coup du N+1ième Noeud
        sinon si Nième.y-N+1ième.y !=0:
            direction = Nième.y-N+1ième.y //cela nous donnes le haut oud le bas. Il faut juste voir la corresspondance avec les commandes
            on diminue les points de mouvement restant du coup du N+1ième Noeud
        else:
            on a une erreur

    */

    int dir;
    int diffX = pathOfVector.at(0)->getX() - state->getPlayer(playerId)->getOwnedFieldObjects()[0]->getPosition().x ;
    int diffY = pathOfVector.at(0)->getY() - state->getPlayer(playerId)->getOwnedFieldObjects()[0]->getPosition().y ;
    for (int i = 0; i<(pathOfVector.size()-1); i++){

        

        if (state->getPlayer(playerId)->getOwnedFieldObjects()[0]->getMovePoints() >= pathOfVector.at(i+1)->getValue() ){
            //Test to know if there still enough move point to make a legal move
            diffX = pathOfVector.at(i+1)->getX() - pathOfVector.at(i)->getX();
            diffY = pathOfVector.at(i+1)->getY() - pathOfVector.at(i)->getY();
            
            if (diffX>0)
            {
                dir = 1;
            }
            else if (diffX<0)
            {
                dir = 3;
            }
            if (diffY>0)
            {
                dir = 2;
            }
            else if (diffY<0)
            {
                dir = 0;
            }


            engine->addCommand(std::make_shared<engine::CommandMove>(dir,0,playerId));
            
        }
        
    }
    engine->addCommand(std::make_shared<engine::CommandEndTurn>(playerId));



    return;
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
    int moveValue;
    sf::Vector2u mapSize = state->getMap()->getSize();
    sf::Vector2u position;
    for (int i = 0 ; i < mapSize.x ; i++)
    {
        for (int j = 0 ; j < mapSize.y ; j++)
        {
            position.x = i;
            position.y = j;
            moveValue = state->getMap()->getTile(position)->attributes["moveCost"];

            m_listNoeud.push_back(std::shared_ptr<Noeud>(new Noeud(moveValue,i,j)));

/*
            if (moveValue == -1 or moveValue >=10)
            {
                std::cout<<moveValue;   
                std::cout<<" ";   
            }
            else
            {
                std::cout<<moveValue;   
                std::cout<<"  ";   
                
            }
  */
        }
        //std::cout<<"\n";
    }


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
    //clearMap();

    std::vector<std::shared_ptr<Noeud> > closedList;
    std::vector<std::shared_ptr<Noeud> > openList;

    openList.push_back(origin);

    while (!openList.empty()){
        std::shared_ptr<Noeud> u = openList.at(noeudPrioritaire(openList));

        for (int i = 0 ; i < openList.size() ; i++)
            if (openList.at(i) == u){
                openList.erase(openList.begin() + i);
                break;
            }


        if (u->getValue() > 0){
            if (u->getX() == destination->getX() && u->getY() == destination->getY()){
                closedList.push_back(u);
            } else {

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
            min = m_listNoeud.at(i)->getHeuristique();
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
        if ( m_listNoeud.at(i)->isNeighbourOf(noeud) && m_listNoeud.at(i) != noeud)
            voisins.push_back(m_listNoeud.at(i));
    return voisins;
}

}



