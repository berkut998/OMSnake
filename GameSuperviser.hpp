#pragma once
#include "AppleMaker.hpp"
#include "Snake.hpp"
#include "IGameObject.hpp"
#include "Button.hpp"

#include <random>
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
    std::vector<sf::RectangleShape>borders;
    sf::Font* font = new sf::Font();
    Button* btnRestart = nullptr;
    bool gameRestarted = false;
    const int borderMargin = 50;
    const int borderSize = 5;
    sf::Vector2f minFieldPos;
    sf::Vector2f maxFieldPos;

    void calculateMinMaxFieldPos();
    bool checkIfAppleCanBeAte();
    void clearAllGameObjects ();
    void createAppleIfNotExist();
    void eatApple();
    bool checkTailCanBeAte();
    void drawGameOverScreen();
    void drawScore();
    void setUpTextVariable();
    void createRestartButton();
    void restartGame();
    void createBorderField();
    bool checkWallCollision();

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
    calculateMinMaxFieldPos();
}

void GameSuperviser::calculateMinMaxFieldPos()
{
    sf::Vector2f windowSize = mainWindow->getDefaultView().getSize();
    windowSize.x-borderMargin*2-borderSize;
    maxFieldPos = sf::Vector2f(windowSize.x-borderMargin*2-borderSize,
    windowSize.y-borderMargin*2-borderSize);
    minFieldPos = sf::Vector2f(borderMargin+borderSize,borderMargin+borderSize);
}

GameSuperviser::~GameSuperviser()
{
    clearAllGameObjects();
}

void GameSuperviser::createRestartButton()
{
    btnRestart = new Button(mainWindow,font,"Restart");
    btnRestart->id = idCounter;
    sf::Vector2f windowSize = mainWindow->getDefaultView().getSize();
    sf::Vector2f btnSize = btnRestart->getSize();
    sf::Vector2f btnPos = sf::Vector2f{windowSize.x/2-btnSize.x/2,windowSize.y/2-btnSize.y/2};
    //std::function<void()> onClickRestart = std::bind(&GameSuperviser::restartGame,this);
    btnRestart->setOnClickFunction(std::bind(&GameSuperviser::restartGame,this));
    btnRestart->setPosition(btnPos);
    btnRestart->alignText(Button::AlignHorizontal::center,Button::AlignVertical::center);
    btnRestart->setTextSize(24);
    btnRestart->visible = false;
    idCounter++;
}

void GameSuperviser::setUpTextVariable()
{
    if (!font->loadFromFile("Font/ArialCE.ttf"))
    {
        std::cout << "can not load font";
    }
    else
    {

        textScore.setFont(*font);
        textScore.setCharacterSize(24);
        textScore.setFillColor(sf::Color::White);
        textScore.setStyle(sf::Text::Bold);
       
        sf::Vector2f windowSize = mainWindow->getDefaultView().getSize();
        float textWidth = textScore.getLocalBounds().width;
        float textHeight = textScore.getLocalBounds().height;
        sf::Vector2f scoreTextPos = sf::Vector2f(windowSize.x/2-textWidth/2,10);
        textScore.setPosition(scoreTextPos);

        textGameOver.setFont(*font);
        textGameOver.setString("Game over");
        textGameOver.setCharacterSize(20);
        textGameOver.setFillColor(sf::Color::White);
        textGameOver.setStyle(sf::Text::Bold);
    }
}

void GameSuperviser::startGame()
{
    setUpTextVariable();
    createBorderField();

    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_distX(minFieldPos.x, maxFieldPos.x);
    int randomX = uniform_distX(e1);
    std::uniform_int_distribution<int> uniform_distY( minFieldPos.y,maxFieldPos.y);
    int randomY = uniform_distY(e1);

    sf::Vector2f snakePos = sf::Vector2f(randomX,randomY);
    snake = new Snake(snakePos);
    snake->id=idCounter;
    idCounter++;
    allGameObjects.push_back(snake);
}



void GameSuperviser::drawAllGameObjects()
{

    drawScore();
    for (const auto &border : borders)
        mainWindow->draw(border);
    if (checkTailCanBeAte()|| checkWallCollision())
    {
        drawGameOverScreen();
        return;
    }
    if (checkIfAppleCanBeAte())
        eatApple();
    createAppleIfNotExist();
    for (const auto &currObject : allGameObjects)
        currObject->draw(mainWindow);
}

void GameSuperviser::drawGameOverScreen()
{
    sf::Vector2f windowSize = mainWindow->getDefaultView().getSize();
    float textWidth = textGameOver.getLocalBounds().width;
    float textHeight = textGameOver.getLocalBounds().height;
    
    sf::Vector2f gameOverTextPos = sf::Vector2f(windowSize.x/2-textWidth/2, windowSize.y/2-textHeight/2);
    textGameOver.setPosition(gameOverTextPos);
    sf::Vector2f btnRestartPos = gameOverTextPos;
    btnRestartPos.y = btnRestartPos.y + 45;
    btnRestartPos.x = btnRestartPos.x-5;
    createRestartButton();

    btnRestart->setPosition(btnRestartPos);
    mainWindow->draw(textGameOver);
    btnRestart->visible = true;
    btnRestart->draw(mainWindow);
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

bool GameSuperviser::checkWallCollision()
{
     sf::FloatRect headBound = snake->getObjectBond();
        size_t bordersSize = borders.size();
        for (size_t i = 0; i < bordersSize; i++)
        {
            sf::FloatRect borderBound = borders[i].getGlobalBounds();
            if (headBound.intersects(borderBound))
                return true;
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
    sf::Vector2f windowMaxSize = mainWindow->getDefaultView().getSize();
    if (appleExist == false)
    {
        currApple =  AppleMaker::createApple(minFieldPos,maxFieldPos);
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
    if (btnRestart != nullptr)
        btnRestart->handleEvent(event);
     for (const auto&  currObject: allGameObjects)
    {

        currObject->handleEvent(event);
        if (gameRestarted)
        {
            gameRestarted = false;  
            break;
        }
            

    }
}

void GameSuperviser::clearAllGameObjects ()
{
    score = 0;
    size_t totalObjects = allGameObjects.size(); 
    for (size_t i =0; i < totalObjects; i++)
    {
        delete allGameObjects[i];
        allGameObjects[i] = nullptr;
    }
    allGameObjects.clear();
    appleExist = false;
        
}

void GameSuperviser::restartGame()
{
    gameRestarted = true;
    delete btnRestart;
    btnRestart = nullptr;
    clearAllGameObjects();
    startGame();
}

void GameSuperviser::createBorderField()
{
    sf::Vector2f windowSize = mainWindow->getDefaultView().getSize();
    sf::Vector2f topBorderSize = sf::Vector2f(windowSize.x-borderMargin*2,borderSize);
    sf::RectangleShape borderTop = sf::RectangleShape(topBorderSize);
    borderTop.setPosition(borderMargin,borderMargin);  
    borders.push_back(borderTop);

    sf::Vector2f leftBorderSize = sf::Vector2f(borderSize,windowSize.y-borderMargin*2);
    sf::RectangleShape leftBorder = sf::RectangleShape(leftBorderSize);
    leftBorder.setPosition(borderMargin,borderMargin);  
    borders.push_back(leftBorder);

    sf::Vector2f rightBorderSize = sf::Vector2f(borderSize,windowSize.y-borderMargin*2);
    sf::RectangleShape rightBorder = sf::RectangleShape(rightBorderSize);
    rightBorder.setPosition(windowSize.x-borderMargin,borderMargin);  
    borders.push_back(rightBorder);

    sf::Vector2f bottomBorderSize = sf::Vector2f(windowSize.x-borderMargin*2+5,borderSize);
    sf::RectangleShape bottomBorder = sf::RectangleShape(bottomBorderSize);
    bottomBorder.setPosition(borderMargin,windowSize.y-borderMargin);  
    borders.push_back(bottomBorder);
}

