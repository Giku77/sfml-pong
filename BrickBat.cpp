#include "stdafx.h"
#include "BrickBat.h"

BrickBat::BrickBat(const std::string& name)
    : GameObject(name)
{
}

void BrickBat::Init()
{
    shape.setSize({ 100.f, 20.f });
    shape.setFillColor(sf::Color::Green);
    Utils::SetOrigin(shape, Origins::MC); 
}

void BrickBat::Release()
{
}

void BrickBat::Reset()
{
    sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
    shape.setPosition(bounds.width / 2.f, bounds.height - 50.f); 
    position = shape.getPosition();

    float halfWidth = shape.getSize().x * 0.5f;
    minX = bounds.left + halfWidth;
    maxX = bounds.left + bounds.width - halfWidth;
}

void BrickBat::Update(float dt)
{
    float axis = InputMgr::GetAxis(Axis::Horizontal);
    dir.x = axis;

    sf::Vector2f pos = shape.getPosition();
    pos += dir * speed * dt;

    pos.x = Utils::Clamp(pos.x, minX, maxX);

    shape.setPosition(pos);
    position = pos;
}

void BrickBat::Draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

