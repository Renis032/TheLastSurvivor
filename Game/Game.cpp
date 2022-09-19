#include "Game.h"

#include "../Common/Common.h"

void Game::_playerMovement(float movementSpeed)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        m_player.move(-movementSpeed, 0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        m_player.move(movementSpeed, 0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        m_player.move(0, -movementSpeed);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        m_player.move(0, movementSpeed);
    }
}

void Game::_shoot()
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        Bullet bullet;
        m_bullets.push_back(bullet);
    }
}

void Game::_drawBullets(sf::RenderWindow& window)
{
    for (const auto& bullet : m_bullets)
    {
        window.draw(bullet.m_bullet);
    }
}

void Game::Run()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "My window");
    window.setVerticalSyncEnabled(true);

    InitPlayer();

    sf::Vector2f playerCenter = sf::Vector2f(m_player.getSize().x / 2, m_player.getSize().y / 2);
    sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
    sf::Vector2f aimDir;
    sf::Vector2f aimDirNorm;

    float movementSpeed = 5.0f;

    while (window.isOpen())
    {
        window.clear(sf::Color::Black);

        playerCenter = sf::Vector2f(m_player.getSize().x / 2, m_player.getSize().y / 2);
        mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));

        aimDir = mousePosition - playerCenter;
        aimDirNorm = Common::Math::normalize(aimDir);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
        }

        _shoot();
        _playerMovement(movementSpeed);
        _drawBullets(window);


        window.draw(m_player);
        window.display();
    }
}

void Game::InitPlayer()
{
    m_player.setSize(sf::Vector2f(25, 40));

}
