#include "stdafx.h"
#include "Bat.h"



void Bat::Init()
{
	shape.setSize({80.f, 5.f});
	shape.setFillColor(sf::Color::White);
	SetOrigin(Origins::BC);

}

void Bat::Release()
{
}

Bat::Bat(const std::string& name)
	:GameObject(name)
{
}

void Bat::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	shape.setRotation(rot);
}

void Bat::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	shape.setPosition(position);
}

void Bat::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	shape.setScale(s);
}

void Bat::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	shape.setOrigin(o);

}

void Bat::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	Utils::SetOrigin(shape, preset);
}
void Bat::Reset()
{
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
	shape.setPosition(bounds.width / 2.f, bounds.height - 20.f);

	sf::Vector2f size = shape.getSize();

	minX = bounds.left + size.x * 0.5f;
	maxX = (bounds.left + bounds.width) - size.x * 0.5f;
}

void Bat::Update(float dt)
{
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
	//std::cout << bounds.width << std::endl;

	
	//if (InputMgr::GetKey({ InputType::Type::Keyboard, sf::Keyboard::Left })) {
		//shape.setPosition(shape.getPosition().x - 1, shape.getPosition().y);
	//}
	//if (InputMgr::GetKey({ InputType::Type::Keyboard, sf::Keyboard::Right })) {
		//shape.setPosition(shape.getPosition().x + 1, shape.getPosition().y);
	//}
	//if(shape.getPosition().x < 0) shape.setPosition(0.f, shape.getPosition().y);
	//if(shape.getPosition().x > bounds.width - 80.f) shape.setPosition(bounds.width - 80.f, shape.getPosition().y);
	
	dir.x = InputMgr::GetAxis(Axis::Horizontal);
	//Utils::Clamp(shape.getPosition().x, minX, maxX);
	SetPosition(shape.getPosition() + dir * speed * dt);

	if(shape.getPosition().x < minX) shape.setPosition(shape.getSize().x / 2.f, shape.getPosition().y);
    if(shape.getPosition().x > maxX) shape.setPosition(bounds.width - shape.getSize().x / 2.f, shape.getPosition().y);
}

void Bat::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}
