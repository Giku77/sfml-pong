#include "stdafx.h"
#include "Ball.h"
#include "Bat.h"
#include "SceneGame.h"

Ball::Ball(const std::string& name)
{
}

void Ball::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	shape.setRotation(rot);
}

void Ball::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	shape.setPosition(position);
}

void Ball::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	shape.setScale(s);
}

void Ball::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	shape.setOrigin(o);

}

void Ball::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	Utils::SetOrigin(shape, preset);
}

void Ball::Init()
{
	shape.setRadius(10.f);
	shape.setFillColor(sf::Color::Yellow);
	SetOrigin(Origins::BC);
}

void Ball::Release()
{
}

void Ball::Reset()
{
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
	shape.setPosition(bounds.width / 2.f, bounds.height - 40.f);

	float radius = shape.getRadius();
	minX = bounds.left + radius;
	maxX = (bounds.left + bounds.width) - radius;

	minY = bounds.top + radius * 2.f;
	maxY = bounds.top + bounds.height + radius * 4.f;

	dir = { 0.f, 0.f };
	speed = 0.f;
}

void Ball::Update(float dt)
{
	sf::Vector2f pos = shape.getPosition() + dir * speed * dt;

	if (pos.x < minX) {
		pos.x = minX;
		dir.x *= -1.f;
	}
	else if (pos.x > maxX) {
		pos.x = maxX;
		dir.x *= -1.f;
	}

	if (pos.y < minY) {
		pos.y = minY;
		dir.y *= -1.f;
	}
	else if (pos.y > maxY) {
		//pos.y = maxY;
		//dir.y *= -1.f;
		if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Game) {
			SceneGame* scene = (SceneGame*) SCENE_MGR.GetCurrentScene();
			scene->SetGameOver();
		}
	}

	if (bat != nullptr) {
		const sf::FloatRect& batBounds = bat->GetGlobalBound();
		if (shape.getGlobalBounds().intersects(batBounds)) {
			pos.y = batBounds.top;
			dir.y *= -1.f;
		}
	}
	SetPosition(pos);
}

void Ball::Draw(sf::RenderWindow& window)
{
	//std::cout << "±×¸²" << std::endl;
	window.draw(shape);
}

void Ball::Fire(const sf::Vector2f& d, float s)
{
	dir = d;
	speed = s;

}
