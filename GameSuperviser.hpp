#pragma once
#include "AppleMaker.hpp"
#include "Snake.hpp"
#include "IGameObject.hpp"
#include "Button.hpp"

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

    bool checkIfAppleCanBeAte();
    void clearAllGameObjects ();
    void createAppleIfNotExist();
    void eatApple();
    bool checkTailCanBeAte();
    void gameOver();
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
}

GameSuperviser::~GameSuperviser()
{
    clearAllGameObjects();
}

void GameSuperviser::createRestartButton()
{
    btnRestart = new Button(mainWindow,font,"Restart");
    btnRestart->id = idCounter;
    sf::Vector2u windowSize = mainWindow->getSize();
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
        textScore.setCharacterSize(14);
        textScore.setFillColor(sf::Color::White);
        textScore.setStyle(sf::Text::Bold | sf::Text::Underlined);
        textScore.setPosition(0, 0);

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
    snake = new Snake();
    snake->id=idCounter;
    idCounter++;
    allGameObjects.push_back(snake);
}

void GameSuperviser::drawAllGameObjects()
{
   
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
    drawScore();
    for (const auto &border : borders)
        mainWindow->draw(border);
}

void GameSuperviser::drawGameOverScreen()
{
    sf::Vector2u windowSize =  mainWindow->getSize();
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
    if (tail.size() > 1)
    {
        size_t tailSize = tail.size();
        for (size_t i = 1; i < tailSize; i++)
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
    sf::Vector2u windowSize = mainWindow->getSize();
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

