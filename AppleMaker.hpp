#pragma once
#include "Apple.hpp"
#include "IGameObject.hpp"

class AppleMaker:public IGameObject
{

public:
    static Apple *createApple(int x_max, int y_max)
    {
        std::srand(std::time(nullptr));;
        int range = x_max + 1;
        int randomX = rand() % range;

        range = y_max + 1;
        int randomY = rand() % range;

        Apple *apple = new Apple(sf::Vector2f(randomX, randomY));
        return apple;
    };
};
