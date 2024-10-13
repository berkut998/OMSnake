#include "IGameObject.hpp"
#include "Control.hpp"
#include <iostream>

class Snake: public IGameObject
{

public:
    struct SnakeBody
    {
        sf::RectangleShape shape;
        Control::Movement currMove = Control::Movement::None;
    };
    void handleEvent(sf::Event *event) override;
    void draw(sf::RenderWindow *window) override;
    std::vector<SnakeBody> getTail();
    sf::FloatRect getObjectBond();
    void grow();
    Snake(sf::Vector2f startPostion );
    ~Snake();

private:
    Control *control;
    const int growSize = 3;
    SnakeBody head;
    std::vector<SnakeBody> tail;
    const sf::Vector2f snakeSize = sf::Vector2f(15,15);
    void moveTailToHead();
};

    Snake::Snake(sf::Vector2f startPostion )
    {
        head = SnakeBody();
        head.shape = sf::RectangleShape(snakeSize);
        head.shape.setFillColor(sf::Color(255,255,255,255));
        control = new Control(&head.shape);
        head.shape.setPosition(startPostion);
    }

    Snake::~Snake()
    {
        delete control;
    }

    std::vector<Snake::SnakeBody> Snake::getTail()
    {
        return tail;
    }
    void Snake::handleEvent(sf::Event *event)
    {
        control->handleEvent(event);
        head.currMove = control->getCurentDirection();
    }

    sf::FloatRect Snake::getObjectBond()
    {
        return head.shape.getGlobalBounds();
    }

    void Snake::draw(sf::RenderWindow *window)
    {
        moveTailToHead();
        control->move();
        for (const auto&  partOfTail: tail)
            window->draw(partOfTail.shape);
        window->draw(head.shape);
    }

    void Snake::moveTailToHead()
    {
        SnakeBody forwardElement = head;
        size_t tailSize = tail.size();
        for (size_t i =0; i < tail.size();i++)
        {
            SnakeBody tmp = tail[i];
            sf::Vector2f nextPos = forwardElement.shape.getPosition();
            tail[i].shape.setPosition(nextPos);
            tail[i].currMove = forwardElement.currMove;
            forwardElement = tmp;
        }
    }

    void Snake::grow()
    {
        for (int i = 0; i < growSize; i++)
        {
            SnakeBody partOfTail;
            SnakeBody lastTailElement;
            if (tail.empty())
                lastTailElement = head;
            else
                lastTailElement = tail.back();
            partOfTail.shape = sf::RectangleShape(snakeSize);
            partOfTail.shape.setFillColor(sf::Color(255, 0, 0, 255));
            partOfTail.currMove = control->getCurentDirection();
            partOfTail.shape.setPosition(-100,-100);//remove from view;
            tail.push_back(partOfTail);
        }
    }


  
