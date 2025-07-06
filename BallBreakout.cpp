#include "stdafx.h"
#include "BallBreakout.h"
#include "BrickBat.h"
#include "SceneGame.h"
#include "UiHud.h"

BallBreakout::BallBreakout()
    : GameObject("BallBreakout")
{
}

BallBreakout::BallBreakout(UiHud* h)
    :hud(h)
{
}

void BallBreakout::SetRotation(float rot)
{
    GameObject::SetRotation(rot);
    shape.setRotation(rot);
}

void BallBreakout::SetScale(const sf::Vector2f& s)
{
    GameObject::SetScale(s);
    shape.setScale(s);
}

void BallBreakout::SetOrigin(const sf::Vector2f& o)
{
    GameObject::SetOrigin(o);
    shape.setOrigin(o);

}

void BallBreakout::SetOrigin(Origins preset)
{
    GameObject::SetOrigin(preset);
    Utils::SetOrigin(shape, preset);
}

void BallBreakout::SetPosition(const sf::Vector2f& pos)
{
    GameObject::SetPosition(pos);
    shape.setPosition(pos);
}

void BallBreakout::Init()
{
    shape.setRadius(10.f);
    shape.setFillColor(sf::Color::White);
    SetOrigin(Origins::MC);
}

void BallBreakout::Release()
{
}

void BallBreakout::Reset()
{
    sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
    shape.setPosition(bounds.width / 2.f, bounds.height - 70.f);

    float r = shape.getRadius();
    minX = bounds.left + r;
    maxX = bounds.left + bounds.width - r;
    minY = bounds.top + r;
    maxY = bounds.top + bounds.height - r;

    dir = { 0.f, 0.f };
    speed = 0.f;
}

void BallBreakout::Fire(const sf::Vector2f& d, float s)
{
    dir = d;
    speed = s;
}

void BallBreakout::resultGame() {
    if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Breakout) {
        SceneGame* scene = (SceneGame*)SCENE_MGR.GetCurrentScene();
        scene->SetGameOver();
    }
}

void BallBreakout::Update(float dt)
{
    if (isFinish && InputMgr::GetKey({ InputType::Type::Keyboard, sf::Keyboard::Enter })) {
        isFinish = false;
        hud->SetShowMsg(false);
        resultGame();
    }
    if (!isFinish) {
        sf::Vector2f pos = shape.getPosition();
        pos += dir * speed * dt;

        if (pos.x < minX)
        {
            pos.x = minX;
            BounceHorizontally();
        }
        else if (pos.x > maxX)
        {
            pos.x = maxX;
            BounceHorizontally();
        }

        if (pos.y < minY)
        {
            pos.y = minY;
            BounceVertically();
        }

        if (pos.y > maxY)
        {
            pos.y = maxY;
            speed = 0.f;
            dir = { 0.f, 0.f };
            hud->SetShowMsg(true);
            hud->SetMsg("GAME OVER");
            isFinish = true;
        }

        if (bat != nullptr) {
            const sf::FloatRect& batBounds = bat->GetGlobalBound();
            if (shape.getGlobalBounds().intersects(batBounds)) {
                pos.y = batBounds.top - shape.getRadius();
                BounceVertically();
            }
        }

        shape.setPosition(pos);
    }
}

void BallBreakout::Draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

void BallBreakout::BounceHorizontally()
{
    dir.x *= -1.f;
}

void BallBreakout::BounceVertically()
{
    dir.y *= -1.f;
}

