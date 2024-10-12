#pragma once
#include "Apple.hpp"
#include "IGameObject.hpp"
#include <random>

class AppleMaker:public IGameObject
{

public:
    static Apple *createApple(int x_max, int y_max)
    {

        // Seed with a real random value, if available
        std::random_device r;

        // Choose a random mean between 1 and 6
        std::default_random_engine e1(r());
        std::uniform_int_distribution<int> uniform_distX(0, x_max);
        int randomX = uniform_distX(e1);

        std::uniform_int_distribution<int> uniform_distY(0, y_max);
        int randomY = uniform_distY(e1);

        // std::srand(std::time(nullptr));;
        // int range = x_max + 1;
        // int randomX = rand() % range;
        // range = y_max + 1;
        // int randomY = rand() % range;
        
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
