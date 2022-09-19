#pragma once
#include <SFML/Graphics.hpp>

#include "../Bullet/Bullet.h"

class Game
{
public:
    void Run();

    void InitPlayer();

private:
    void _shoot();
    void _playerMovement(float movementSpeed);

private:
    sf::RectangleShape m_player;
    std::vector<Bullet> m_bullets;
    void _drawBullets(sf::RenderWindow& window);
};
