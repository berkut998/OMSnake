#pragma once
#include "IGameObject.hpp"

class Apple : public IGameObject
{
private:
    /* data */
    sf::CircleShape currShape;
public:
    Apple(sf::Vector2f coord, float radius, std::size_t countPoint);
    void draw(sf::RenderWindow *window) override;
    void handleEvent(sf::Event *event) override; 
    sf::FloatRect getObjectBond();
    ~Apple();
};

Apple::Apple(sf::Vector2f coord, float radius, std::size_t countPoint)
{
    currShape = sf::CircleShape(radius, countPoint);
    currShape.move(coord);
    currShape.setFillColor(sf::Color(255,0,0,255));
}

sf::FloatRect Apple::getObjectBond()
{
    return currShape.getGlobalBounds();
}

void Apple::draw(sf::RenderWindow *window)
{
    window->draw(currShape);
}

void Apple::handleEvent(sf::Event *event)
{}

Apple::~Apple()
{
}
