#pragma once
#include "Apple.hpp"
#include "IGameObject.hpp"
#include <random>

class AppleMaker:public IGameObject
{

public:
    static Apple *createApple(sf::Vector2f minPos, sf::Vector2f maxPos)
    {
        std::random_device r;
        std::default_random_engine e1(r());

        std::uniform_int_distribution<int> uniform_distX(minPos.x, maxPos.x);
        int randomX = uniform_distX(e1);
        std::uniform_int_distribution<int> uniform_distY(minPos.y, maxPos.y);
        int randomY = uniform_distY(e1);
        
        int radiusApple = 10.f;
        int countCurclePoint = 10.f;
        if (randomX + radiusApple * 2 > maxPos.x)
            randomX -= radiusApple * 2;
        if (randomY + radiusApple * 2 > maxPos.y)
            randomY -= radiusApple * 2;
        sf::Vector2f appleCoord = sf::Vector2f(randomX, randomY);
        Apple *apple = new Apple(appleCoord,radiusApple,countCurclePoint);
        return apple;
    };
};
