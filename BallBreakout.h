#pragma once
#include "GameObject.h"
class BrickBat;
class UiHud;

class BallBreakout : public GameObject
{
protected:
    sf::CircleShape shape;
    sf::Vector2f dir = { 0.f, 0.f };
    float speed = 0.f;

    float minX = 0.f, maxX = 0.f;
    float minY = 0.f, maxY = 0.f;

    bool isFinish = false;

    BrickBat* bat = nullptr;
    UiHud* hud = nullptr;

public:
    BallBreakout();
    BallBreakout(UiHud* h);
    ~BallBreakout() = default;


    void resultGame();
    void SetRotation(float rot)  override;
    void SetPosition(const sf::Vector2f& pos) override;
    void SetScale(const sf::Vector2f& s) override;
    void SetOrigin(const sf::Vector2f& o) override;
    void SetOrigin(Origins preset) override;

    const sf::CircleShape& getShape() const { return shape; }


    void Fire(const sf::Vector2f& d, float s);
    void BounceHorizontally();
    void BounceVertically();

    const sf::FloatRect& GetGlobalBounds() const { return shape.getGlobalBounds(); }
    void SetBat(BrickBat* b) { bat = b; }

    void Init() override;
    void Release() override;
    void Reset() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;
};

