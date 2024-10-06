#include "IGameObject.hpp"
#include "Control.hpp"
#include <iostream>

class Snake: public IGameObject
{
private:
    Control* control;
    sf::RectangleShape head;
    struct SnakeTail
    {
        sf::RectangleShape shape;
    };
    std::vector<SnakeTail> tail;
    void setPositionForTailElement(SnakeTail &tail, sf::RectangleShape relativeElement);
    void moveTailToHead();
public:

    void handleEvent(sf::Event *event) override;
    void draw(sf::RenderWindow *window) override;
    sf::FloatRect getObjectBond();
    void grow();
    Snake();
    ~Snake();

};

    Snake::Snake()
    {
        head = sf::RectangleShape(sf::Vector2f(5,5));
        head.setFillColor(sf::Color(255,255,255,255));
        control = new Control(&head);
    }

    Snake::~Snake()
    {
        delete control;
    }

    void Snake::handleEvent(sf::Event *event)
    {
        control->handleEvent(event);
    }

    sf::FloatRect Snake::getObjectBond()
    {
        return head.getGlobalBounds();
    }

    void Snake::draw(sf::RenderWindow *window)
    {
        control->move();
        moveTailToHead();
        for (const auto&  partOfTail: tail)
            window->draw(partOfTail.shape);
        window->draw(head);
    }

    void Snake::grow()
    {
        SnakeTail partOfTail;
        sf::RectangleShape lastTailElement;
        if (tail.empty())
            lastTailElement = head;
        else
            lastTailElement = tail.back().shape;
        partOfTail.shape = sf::RectangleShape(sf::Vector2f(5, 5));
        partOfTail.shape.setFillColor(sf::Color(255, 255, 255, 255));
        setPositionForTailElement(partOfTail, lastTailElement);
        tail.push_back(partOfTail);
    }

    void Snake::moveTailToHead()
    {
        
        sf::Vector2f currPostion = head.getPosition();
        size_t tailSize = tail.size();
        for(size_t i =0; i < tailSize ; i++)
        {
            std::cout << currPostion.x << std::endl;
            sf::Vector2f tmpRect =tail[i].shape.getPosition();
            tail[i].shape.move(currPostion.x,currPostion.y);
            currPostion = tmpRect;
        }            
    }

    void Snake::setPositionForTailElement(SnakeTail &tail, sf::RectangleShape relativeElement)
    {
        Control::Movement currDirection = control->getCurentDirection();
        sf::FloatRect coordRelatElem = relativeElement.getGlobalBounds(); 
        float x = 0;
        float y = 0;
        if (currDirection == Control::Movement::Down)
        {
            x = coordRelatElem.left;
            y = coordRelatElem.top - coordRelatElem.height;
        }
        else if (currDirection == Control::Movement::Left)
        {
            x = coordRelatElem.left + coordRelatElem.width;
            y = coordRelatElem.top;
           
        }
        else if (currDirection == Control::Movement::Up)
        {
            x = coordRelatElem.left;
            y = coordRelatElem.top + coordRelatElem.height;
        }
        else if (currDirection == Control::Movement::Right)
        {
            x = coordRelatElem.left - coordRelatElem.width;
            y = coordRelatElem.top;
        }
        std::cout<<x<<std::endl;
        tail.shape.move(x, y);
    }
    // not sure what use upper or below method need more tests
    // void Snake::setPositionForTailElement(SnakeTail &tail, sf::RectangleShape relativeElement)
    // {
    //     Control::Movement currDirection = control->getCurentDirection();
    //     sf::Vector2f coordRelatElem = relativeElement.getPosition(); 
    //     float x = 0;
    //     float y = 0;
    //     if (currDirection == Control::Movement::Down)
    //     {
    //         x = coordRelatElem.x;
    //         y = coordRelatElem.y - relativeElement.getSize().y;
    //     }
    //     else if (currDirection == Control::Movement::Left)
    //     {
    //         x = coordRelatElem.x + relativeElement.getSize().x;
    //         y = coordRelatElem.y;
           
    //     }
    //     else if (currDirection == Control::Movement::Up)
    //     {
    //         x = coordRelatElem.x;
    //         y = coordRelatElem.y + relativeElement.getSize().y;
    //     }
    //     else if (currDirection == Control::Movement::Right)
    //     {
    //         x = coordRelatElem.x - relativeElement.getSize().x;
    //         y = coordRelatElem.y;
    //     }
    //     std::cout<<x<<std::endl;
    //      tail.shape.move(x, y);
    // }
