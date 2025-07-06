#include "stdafx.h"
#include "Ball.h"
#include "Bat.h"
#include "SceneGame.h"
#include "UiHud.h"

Ball::Ball(const std::string& name)
{
}

Ball::Ball(UiHud* u)
	:hud(u)
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
	shape.setPosition(pos);
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
	SetOrigin(Origins::ML);
}

void Ball::Release()
{
}

void Ball::Reset()
{
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
	shape.setPosition(40.f, bounds.height / 2.f);

	float radius = shape.getRadius();
	minX = bounds.left + radius - 50.f;
	maxX = (bounds.left + bounds.width) - radius + 50.f;

	minY = bounds.top + radius;
	maxY = bounds.top + bounds.height - radius;

	dir = { 0.f, 0.f };
	speed = 0.f;
}

void Ball::resultGame() {
	if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Game) {
		SceneGame* scene = (SceneGame*)SCENE_MGR.GetCurrentScene();
		scene->SetGameOver();
	}
}

void Ball::Update(float dt)
{
	if (isFinish && InputMgr::GetKey({ InputType::Type::Keyboard, sf::Keyboard::Enter })) {
		isFinish = false;
		hud->SetShowMsg(false);
		resultGame();
	}
	if(!isFinish) {
		sf::Vector2f pos = shape.getPosition() + dir * speed * dt;

		if (pos.x < minX) {
			//pos.x = minX;
			//dir.x *= -1.f;
			hud->SetShowMsg(true);
			hud->SetMsg("PLAYER2 WIN");
			isFinish = true;
		}
		else if (pos.x > maxX) {
			//pos.x = maxX;
			//dir.x *= -1.f;
			hud->SetShowMsg(true);
			hud->SetMsg("PLAYER1 WIN");
			isFinish = true;
		}

		if (pos.y < minY) {
			pos.y = minY;
			dir.y *= -1.f;
		}
		else if (pos.y > maxY) {
			pos.y = maxY;
			dir.y *= -1.f;
		}

		if (bat != nullptr) {
			const sf::FloatRect& batBounds = bat->GetGlobalBound();
			const sf::FloatRect batBounds2 = bat->GetGlobalBound2();
			if (shape.getGlobalBounds().intersects(batBounds)) {
				pos.x = 40.f;
				dir.x *= -1.f;
			}
			if (shape.getGlobalBounds().intersects(batBounds2)) {
				pos.x = batBounds2.left - 40.f;
				dir.x *= -1.f;
			}
		}
		SetPosition(pos);
	}
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
