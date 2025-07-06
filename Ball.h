#pragma once
#include "GameObject.h"

class Bat;
class UiHud;
class Ball :
    public GameObject
{
protected:
    sf::CircleShape shape;
    float speed = 500.f;
    sf::Vector2f dir;

    Bat* bat = nullptr;
    UiHud* hud = nullptr;

    float minX = 0.f;
    float maxX = 0.f;
    float minY = 0.f;
    float maxY = 0.f;

    bool isFinish = false;

public:
    Ball(const std::string& name = "");
    Ball(UiHud* u);
    ~Ball() = default;

    void SetRotation(float rot)  override;
    void SetPosition(const sf::Vector2f& pos) override;
    void SetScale(const sf::Vector2f& s) override;
    void SetOrigin(const sf::Vector2f& o) override;
    void SetOrigin(Origins preset) override;

    void setBat(Bat* b) { bat = b; }

    void resultGame();

    void Init() override;

    void Release() override;

    void Reset() override;

    void Update(float dt) override;

    void Draw(sf::RenderWindow& window) override;

    void Fire(const sf::Vector2f& d, float s);
};

