#pragma once
#include "Dependency/SFML-2.6.1/include/SFML/Graphics.hpp"
#include "IGameObject.hpp"
#include <iostream> //remove after debug
class Control
{
public:
    enum class Movement
    {
        None,
        Up,
        Down,
        Left,
        Right
    };
    Control(sf::Shape *shape);
    ~Control();
    void move();
    void handleEvent(sf::Event *event);
    sf::FloatRect getObjectBond();
    Movement getCurentDirection();
    float speed = 2;
    // float acceleration  =1;
    float maxSpeed = 60;

private:
    /* data */
    sf::Shape *currShape;
    Movement currMoveTo = Movement::None;
    void changeMovement(sf::Event *event);
};

void Control::handleEvent(sf::Event *event){
    changeMovement(event);
}
void Control::move()
{
    // if (maxSpeed < speed);
    //     speed +=acceleration;
    float x = 0;
    float y = 0;
    if (currMoveTo == Movement::Left)
        x -= 1.f;
    else if (currMoveTo == Movement::Right)
        x += 1.f;
    else if (currMoveTo == Movement::Up)
        y -= 1.f;
    else if (currMoveTo == Movement::Down)
        y += 1.f;
    currShape->move(x * speed, y * speed);
}

void Control::changeMovement(sf::Event *event)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        currMoveTo = Movement::Left;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        currMoveTo = Movement::Right;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        currMoveTo = Movement::Up;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        currMoveTo = Movement::Down;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        currMoveTo = Movement::None;
}

Control::Movement Control::getCurentDirection()
{
    return currMoveTo;
}

Control::Control(sf::Shape* shape)
{
    currShape = shape;
}

Control::~Control()
{
}
