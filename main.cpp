#include "Dependency/SFML-2.6.1/include/SFML/Graphics.hpp"
#include "GameSuperviser.hpp"

int main()
{
    
    sf::RenderWindow window(sf::VideoMode(200, 200), "OMSnake");
    window.setFramerateLimit(60);
    GameSuperviser game = GameSuperviser(&window);
    game.startGame();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            game.sendEventToAllGameObjects(&event);

        }

        window.clear();
        game.drawAllGameObjects();
        window.display();
        
        game.drawAllGameObjects();
    }
    return 0;
}
