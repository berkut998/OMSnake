#pragma once
#include "Dependency/SFML-2.6.1/include/SFML/Graphics.hpp"
#include "IGameObject.hpp"

class Player:public IGameObject
{
private:
    /* data */
    sf::RectangleShape currShape = sf::RectangleShape(sf::Vector2f(25, 25));
    enum class  Movement
    {
        None,
        Up,
        Down,
        Left,
        Right
    };

    Movement currMoveTo = Movement::None;
    void changeMovement(sf::Event *event);
    void move();
    
public:
    Player(/* args */);
    ~Player();

    void handleEvent(sf::Event *event) override;
    void draw(sf::RenderWindow *window) override;
    sf::FloatRect getObjectBond();
    float speed = 1;
    //float acceleration  =1;
    float maxSpeed = 30;
};

void Player::handleEvent(sf::Event *event)
{
    changeMovement(event);
}

sf::FloatRect Player::getObjectBond()
{
    return currShape.getGlobalBounds();
}

void Player::draw(sf::RenderWindow *window)
{
    move();
    window->draw(currShape);
}

void Player::move()
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
    currShape.move(x * speed, y * speed);
}

void Player::changeMovement(sf::Event *event)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        currMoveTo = Movement::Left;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        currMoveTo = Movement::Right;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        currMoveTo = Movement::Up;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        currMoveTo = Movement::Down;
}

Player::Player(/* args */)
{

}

Player::~Player()
{
}
