#include "stdafx.h"
#include "Brick.h"

Brick::Brick()
    : GameObject("Brick")
{
}

void Brick::Init()
{
    shape.setSize({ 50.f, 20.f });
    shape.setFillColor(sf::Color::Magenta);
    Utils::SetOrigin(shape, Origins::MC);  
}

void Brick::Reset()
{
    isDestroyed = false;
    SetActive(true);  
}

void Brick::Update(float dt)
{
   
}

void Brick::Draw(sf::RenderWindow& window)
{
    if (!isDestroyed)
        window.draw(shape);
}

void Brick::Destroy()
{
    isDestroyed = true;
    SetActive(false); 
}

void Brick::SetPosition(const sf::Vector2f& pos)
{
    shape.setPosition(pos);
}

void Brick::SetSize(const sf::Vector2f& size)
{
    shape.setSize(size);
    Utils::SetOrigin(shape, Origins::MC); 
}

void Brick::SetColor(const sf::Color& color)
{
    shape.setFillColor(color);
}

void Brick::Release()
{
}
