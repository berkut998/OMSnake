#include "IGameObject.hpp"
#include "Player.hpp"
class Snake: public IGameObject
{
private:
    Player* p = nullptr;
    struct SnakeTail
    {
        sf::RectangleShape tail;
    };
    std::vector<SnakeTail> tail;
public:
    void tt ();
    Snake(Player *player)
    {
        p = player;
    }

};


