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
        
        int radiusApple = 10.f;
        int countCurclePoint = 10.f;
        if (randomX + radiusApple * 2 > x_max)
            randomX -= radiusApple * 2;
        if (randomY + radiusApple * 2 > y_max)
            randomY -= radiusApple * 2;
        sf::Vector2f appleCoord = sf::Vector2f(randomX, randomY);
        Apple *apple = new Apple(appleCoord,radiusApple,countCurclePoint);
        return apple;
    };
};
