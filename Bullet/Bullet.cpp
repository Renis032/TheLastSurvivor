#include "Bullet.h"

Bullet::Bullet(float radius) :
    m_currentVelocity(0.0f, 0.0f), m_maxSpeed(15.0f)
{
    m_bullet.setRadius(radius);
    m_bullet.setFillColor(sf::Color::Red);
}
