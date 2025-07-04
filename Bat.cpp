#include "stdafx.h"
#include "Bat.h"



void Bat::Init()
{
	shape.setSize({ 100.f, 5.f });
	shape.setFillColor(sf::Color::White);

	shape2.setSize({ 100.f, 5.f });
	shape2.setFillColor(sf::Color::White);
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
	shape2.setRotation(rot);
}

void Bat::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	shape.setPosition(position);
	shape2.setPosition(position);
}

void Bat::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	shape.setScale(s);
	shape2.setScale(s);
}

void Bat::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	shape.setOrigin(o);
	shape2.setOrigin(o);
}

void Bat::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	Utils::SetOrigin(shape, preset);
	Utils::SetOrigin(shape2, preset);
}
void Bat::Reset()
{
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
	shape.setPosition(bounds.width / 2.f, bounds.height - 20.f);
	shape2.setPosition(bounds.width / 2.f, 20.f);
	position = shape.getPosition();

	sf::Vector2f size = shape.getSize();

	minX = bounds.left + size.x * 0.5f;
	maxX = (bounds.left + bounds.width) - size.x * 0.5f;
}

void Bat::Update(float dt)
{
	position = shape.getPosition();
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
	//std::cout << bounds.width << std::endl;

	
	if (InputMgr::GetKey({ InputType::Type::Keyboard, sf::Keyboard::Left })) {
		dir.x = -1.f;
		shape.setPosition(shape.getPosition() + dir * speed * dt);
	}
	if (InputMgr::GetKey({ InputType::Type::Keyboard, sf::Keyboard::Right })) {
		dir.x = 1.f;
		shape.setPosition(shape.getPosition() + dir * speed * dt);
	}

	if (InputMgr::GetKey({ InputType::Type::Keyboard, sf::Keyboard::A })) {
		dir2.x = -1.f;
		shape2.setPosition(shape2.getPosition() + dir2 * speed * dt);
	}
	if (InputMgr::GetKey({ InputType::Type::Keyboard, sf::Keyboard::D })) {
		dir2.x = 1.f;
		shape2.setPosition(shape2.getPosition() + dir2 * speed * dt);
	}
	//if(shape.getPosition().x < 0) shape.setPosition(0.f, shape.getPosition().y);
	//if(shape.getPosition().x > bounds.width - 80.f) shape.setPosition(bounds.width - 80.f, shape.getPosition().y);
	
	//dir.x = InputMgr::GetAxis(Axis::Horizontal);
	//dir2.x = InputMgr::GetAxis(Axis::Horizontal);
	//Utils::Clamp(shape.getPosition().x, minX, maxX);
	//shape.setPosition(shape.getPosition() + dir * speed * dt);
	//shape2.setPosition(shape2.getPosition() + dir2 * speed * dt);

	if (shape2.getPosition().x < minX) shape2.setPosition(shape2.getSize().x / 2.f, shape2.getPosition().y);
	if (shape2.getPosition().x > maxX) shape2.setPosition(bounds.width - shape2.getSize().x / 2.f, shape2.getPosition().y);

	if(shape.getPosition().x < minX) shape.setPosition(shape.getSize().x / 2.f, shape.getPosition().y);
    if(shape.getPosition().x > maxX) shape.setPosition(bounds.width - shape.getSize().x / 2.f, shape.getPosition().y);
}

void Bat::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
	window.draw(shape2);
}
