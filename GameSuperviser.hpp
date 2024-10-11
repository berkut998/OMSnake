#pragma once
#include "AppleMaker.hpp"
#include "Snake.hpp"
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
    Snake* snake = nullptr;
    int idCounter = 0;
    int score = 0;
    sf::Text textScore;
    sf::Text textGameOver;
    sf::Font font;

    bool checkIfAppleCanBeAte();
    void clearAllGameObjects ();
    void createAppleIfNotExist();
    void eatApple();
    bool checkTailCanBeAte();
    void gameOver();
    void drawGameOverScreen();
    void drawScore();
    void drawRestartButton();
    void setUpTextVariable();

public:
    GameSuperviser(sf::RenderWindow *window);
    void startGame ();
    void drawAllGameObjects();
    void sendEventToAllGameObjects(sf::Event *event);
    ~GameSuperviser();
};


GameSuperviser::GameSuperviser(sf::RenderWindow *window)
{
   

    setUpTextVariable();
    mainWindow = window;
}

void GameSuperviser::setUpTextVariable()
{
    if (!font.loadFromFile("Font/ArialCE.ttf"))
    {
        std::cout << "can not load font";
    }
    else
    {
        textScore.setFont(font);
        textScore.setCharacterSize(14);
        textScore.setFillColor(sf::Color::White);
        textScore.setStyle(sf::Text::Bold | sf::Text::Underlined);
        textScore.setPosition(0, 0);

        textGameOver.setFont(font);
        textGameOver.setString("Game over");
        textGameOver.setCharacterSize(20);
        textGameOver.setFillColor(sf::Color::White);
        textGameOver.setStyle(sf::Text::Bold);
    }
}


GameSuperviser::~GameSuperviser()
{
    clearAllGameObjects();
}


void GameSuperviser::startGame()
{
    snake = new Snake();
    snake->id=idCounter;
    idCounter++;
    allGameObjects.push_back(snake);
}








void GameSuperviser::drawAllGameObjects()
{
   
    if (checkTailCanBeAte())
    {
        drawGameOverScreen();
        return;
    }
    if (checkIfAppleCanBeAte())
        eatApple();
    createAppleIfNotExist();
    for (const auto &currObject : allGameObjects)
        currObject->draw(mainWindow);
    drawScore();
}

void GameSuperviser::drawGameOverScreen()
{
    sf::Vector2u windowSize =  mainWindow->getSize();
    float textWidth = textGameOver.getLocalBounds().width;
    float textHeight = textGameOver.getLocalBounds().height;
    textGameOver.setPosition(windowSize.x/2-textWidth/2, windowSize.y/2-textHeight/2);
    mainWindow->draw(textGameOver);
    drawRestartButton();
}

void GameSuperviser::drawRestartButton()
{
    sf::RectangleShape rect;
    sf::Vector2f rectSize = sf::Vector2f{60.f,20.f};
    rect.setSize(rectSize);
    sf::FloatRect rectGameOver = textGameOver.getLocalBounds();
    //tmp solution;
    float textWidth = textGameOver.getLocalBounds().width;
    float textHeight = textGameOver.getLocalBounds().height;
    sf::Vector2u windowSize =  mainWindow->getSize();
    rect.setPosition(windowSize.x/2-textWidth/2, windowSize.y/2-textHeight/2);
    rect.setFillColor(sf::Color::Red);
    mainWindow->draw(rect);
}

bool GameSuperviser::checkTailCanBeAte()
{
    sf::FloatRect headBound = snake->getObjectBond();
    std::vector<Snake::SnakeBody> tail = snake->getTail();
    if (tail.size() > 6)
    {
        size_t tailSize = tail.size();
        for (size_t i = 6; i < tailSize; i++)
        {
            sf::FloatRect tailBouds = tail[i].shape.getGlobalBounds();
            if (headBound.intersects(tailBouds))
                return true;
        }
    }
    return false;
}
bool GameSuperviser::checkIfAppleCanBeAte()
{
    if (snake != nullptr && currApple != nullptr)
    {
        sf::FloatRect playerRect = snake->getObjectBond();
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
            score++;
            std::cout << "Score:"<<score <<std::endl;
            allGameObjects.erase(allGameObjects.begin() + i);
            delete currApple;
            currApple = nullptr;
            appleExist = false;
            snake->grow();
            break;
        }        
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

void GameSuperviser::drawScore()
{
    textScore.setString("Score:" + std::to_string(score));
    mainWindow->draw(textScore);
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



