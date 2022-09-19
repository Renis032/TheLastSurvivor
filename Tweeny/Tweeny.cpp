#include "Tweeny.h"
#include <cmath>
#include <iostream>

namespace Core
{

void Tweeny::Start(float begin, float end, float duration)
{
    m_elapsedDuration = {};
    m_currentValue = {};

    m_beginValue = begin;
    m_endValue = end;
    m_duration = duration;
}

void Tweeny::Update(float deltaTime)
{
    if(IsFinished())
    {
        return;
    }

    m_elapsedDuration += deltaTime;
    m_elapsedDuration = std::fmin(m_elapsedDuration, m_duration);

    float progress = m_elapsedDuration / m_duration;

    float distance = m_endValue - m_beginValue;
    float elapsedDistance = distance * progress;
    m_currentValue = m_beginValue + elapsedDistance;
}

float Tweeny::GetCurrentValue() const
{
    return m_currentValue;
}

bool Tweeny::IsFinished() const
{
    return m_elapsedDuration >= m_duration;
}

ITweeny::Ptr PositionTween::MoveFromTo(sf::Transformable& transformable, sf::Vector2f begin, sf::Vector2f end, float duration)
{
    auto positionTween = std::make_shared<PositionTween>();
    positionTween->m_transformable = &transformable;
    positionTween->m_xPosition.Start(begin.x, end.x, duration);
    positionTween->m_yPosition.Start(begin.y, end.y, duration);
    return std::move(positionTween);
}

ITweeny::Ptr PositionTween::MoveTo(sf::Transformable&transformable, sf::Vector2f end, float duration)
{
    sf::Vector2f begin = transformable.getPosition();
    auto positionTween = std::make_shared<PositionTween>();
    positionTween->m_transformable = &transformable;
    positionTween->m_xPosition.Start(begin.x, end.x, duration);
    positionTween->m_yPosition.Start(begin.y, end.y, duration);
    return std::move(positionTween);
}

void PositionTween::Update(float deltaTime)
{
    m_xPosition.Update(deltaTime);
    m_yPosition.Update(deltaTime);
    m_transformable->setPosition(m_xPosition.GetCurrentValue(), m_yPosition.GetCurrentValue());
}

bool PositionTween::IsFinished() const
{
    return m_xPosition.IsFinished() && m_yPosition.IsFinished();
}

void SequenceTween::Start(const std::vector<ITweeny::Ptr> &tweenies)
{
    m_tweenies = tweenies;
}

void SequenceTween::Update(float deltaTime)
{
    if(IsFinished())
    {
        return;
    }

    auto& currentTween = m_tweenies[m_currentIndex];
    currentTween->Update(deltaTime);
    if(currentTween->IsFinished())
    {
        m_currentIndex++;
    }
}

bool SequenceTween::IsFinished() const
{
    return m_currentIndex == m_tweenies.size();
}

} // Core
