#pragma once
#include "Dependency/SFML-2.6.1/include/SFML/Graphics.hpp"

class IGameObject
{
private:
    /* data */
public:
    virtual void handleEvent(sf::Event *event){};
    virtual void draw(sf::RenderWindow *window){};
    int id;
};

