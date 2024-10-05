#pragma once
#include "AppleMaker.hpp"
#include "Player.hpp"
#include "IGameObject.hpp"
#include <iostream>
class GameSuperviser
{
private:
    /* data */
    std::vector<IGameObject*> allGameObjects;
    sf::RenderWindow *mainWindow;
    bool appleExist = false;
    Apple* currApple = nullptr;
    Player* p = nullptr;
    int idCounter = 0;

    bool checkIfAppleCanBeAte();
    void clearAllGameObjects ();
    void createAppleIfNotExist();
    void eatApple();

public:
    GameSuperviser(sf::RenderWindow *window);
    void startGame ();
    void drawAllGameObjects();
    void sendEventToAllGameObjects(sf::Event *event);
    ~GameSuperviser();
};


GameSuperviser::GameSuperviser(sf::RenderWindow *window)
{
    mainWindow = window;
}

GameSuperviser::~GameSuperviser()
{
    clearAllGameObjects();
}

void GameSuperviser::startGame()
{
    p = new Player();
    p->id=idCounter;
    idCounter++;
    allGameObjects.push_back(p);
}



void GameSuperviser::createAppleIfNotExist()
{
    sf::Vector2u windowMaxSize = mainWindow->getSize();
    if (appleExist == false)
    {
        currApple =  AppleMaker::createApple(windowMaxSize.x,windowMaxSize.y);
        currApple->id = idCounter;
        idCounter++;
        allGameObjects.push_back(currApple);
        appleExist = true;
    }
}

bool GameSuperviser::checkIfAppleCanBeAte()
{
    if (p != nullptr && currApple != nullptr)
    {
        sf::FloatRect playerRect = p->getObjectBond();
        sf::FloatRect appleRect = currApple->getObjectBond();
        if (playerRect.intersects(appleRect))
            return true;
    }
    return false;
}

void GameSuperviser::eatApple()
{

    size_t countObjects = allGameObjects.size();
    for (size_t i =0; i < countObjects; i++)
        if (allGameObjects[i]->id == currApple->id)
        {
            allGameObjects.erase(allGameObjects.begin() + i);
            delete currApple;
            currApple = nullptr;
            appleExist = false;
            break;
        }        
}

void GameSuperviser::drawAllGameObjects()
{
    if (checkIfAppleCanBeAte())
        eatApple();
    createAppleIfNotExist();
    for (const auto &currObject : allGameObjects)
        currObject->draw(mainWindow);
}

void GameSuperviser::sendEventToAllGameObjects(sf::Event *event)
{
     for (const auto&  currObject: allGameObjects)
        currObject->handleEvent(event);
}

void GameSuperviser::clearAllGameObjects ()
{
    size_t totalObjects = allGameObjects.size(); 
    for (size_t i =0; i < totalObjects; i++)
        delete allGameObjects[i];
}



