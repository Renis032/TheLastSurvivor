#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include <memory>

namespace Core
{

class Tweeny
{
public:
    void Start(float begin, float end, float duration);
    void Update(float deltaTime);
    float GetCurrentValue() const;
    bool IsFinished() const;
private:
    float m_beginValue{};
    float m_endValue{};
    float m_duration{};

    float m_currentValue{};
    float m_elapsedDuration{};
};

class ITweeny
{
public:
    using Ptr = std::shared_ptr<ITweeny>;
    virtual ~ITweeny() = default;

    virtual void Update(float deltaTime) = 0;
    virtual bool IsFinished() const = 0;
};

class PositionTween : public ITweeny
{
public:
    static ITweeny::Ptr MoveFromTo(sf::Transformable& transformable, sf::Vector2f begin, sf::Vector2f end, float duration);
    static ITweeny::Ptr MoveTo(sf::Transformable& transformable, sf::Vector2f end, float duration);

    void Update(float deltaTime) override;
    bool IsFinished() const override;
private:
    sf::Transformable* m_transformable;
    Tweeny m_xPosition;
    Tweeny m_yPosition;
};

class SequenceTween
{
public:
    void Start(const std::vector<ITweeny::Ptr>& tweenies);
    void Update(float deltaTime);
    bool IsFinished() const;
private:
    std::vector<ITweeny::Ptr> m_tweenies;
    size_t m_currentIndex = 0;
};

} // Core
