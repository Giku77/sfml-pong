#include "stdafx.h"
#include "Bat.h"



void Bat::Init()
{
	shape.setSize({ 5.f, 100.f });
	shape.setFillColor(sf::Color::White);

	shape2.setSize({ 5.f, 100.f });
	shape2.setFillColor(sf::Color::White);
	SetOrigin(Origins::MR);

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
	shape.setPosition(20.f, bounds.height / 2.f);
	shape2.setPosition(bounds.width - 20.f, bounds.height / 2.f);
	position = shape.getPosition();

	sf::Vector2f size = shape.getSize();

	//minX = bounds.left + size.x * 0.5f;
	//maxX = (bounds.left + bounds.width) - size.x * 0.5f;
	minY = bounds.top + size.y * 0.5f;
	maxY = (bounds.top + bounds.height) - size.y * 0.5f;
}

void Bat::Update(float dt)
{
	position = shape.getPosition();
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
	//std::cout << bounds.width << std::endl;

	
	/*if (InputMgr::GetKey({ InputType::Type::Keyboard, sf::Keyboard::Up })) {
		dir2.y = -1.f;
		shape2.setPosition(shape2.getPosition() + dir2 * speed * dt);
	}
	if (InputMgr::GetKey({ InputType::Type::Keyboard, sf::Keyboard::Down})) {
		dir2.y = 1.f;
		shape2.setPosition(shape2.getPosition() + dir2 * speed * dt);
	}

	if (InputMgr::GetKey({ InputType::Type::Keyboard, sf::Keyboard::W })) {
		dir.y = -1.f;
		shape.setPosition(shape.getPosition() + dir * speed * dt);
	}
	if (InputMgr::GetKey({ InputType::Type::Keyboard, sf::Keyboard::S })) {
		dir.y = 1.f;
		shape.setPosition(shape.getPosition() + dir * speed * dt);
	}*/
	dir.y = InputMgr::GetAxis(Axis::Vertical);    
	shape.setPosition(shape.getPosition() + dir * speed * dt);

	dir2.y = InputMgr::GetAxis(Axis::Vertical2);  
	shape2.setPosition(shape2.getPosition() + dir2 * speed * dt);


	/*shape.setPosition(Utils::Clamp(shape.getPosition(),
		{ shape.getPosition().x, minY },
		{ shape.getPosition().x, maxY }));

	shape2.setPosition(Utils::Clamp(shape2.getPosition(),
		{ shape2.getPosition().x, minY },
		{ shape2.getPosition().x, maxY }));*/
	
	if (shape2.getPosition().y < minY) shape2.setPosition(shape2.getPosition().x, shape2.getSize().y / 2.f);
	if (shape2.getPosition().y > maxY) shape2.setPosition(shape2.getPosition().x, bounds.height - shape2.getSize().y / 2.f);

	if(shape.getPosition().y < minY) shape.setPosition(shape.getPosition().x, shape.getSize().y / 2.f);
    if(shape.getPosition().y > maxY) shape.setPosition(shape.getPosition().x, bounds.height - shape.getSize().y / 2.f);
}

void Bat::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
	window.draw(shape2);
}
