#pragma once

#include <SFML/Graphics.hpp>

class Bullet
{
public:
    Bullet(float radius = 5.0f);

    sf::CircleShape m_bullet;

    float m_maxSpeed;
    sf::Vector2f m_currentVelocity;
};
