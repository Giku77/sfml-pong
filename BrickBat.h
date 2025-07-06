#pragma once
#include "GameObject.h"

class BrickBat : public GameObject
{

protected:
    sf::RectangleShape shape;
    sf::Vector2f dir = { 0.f, 0.f };
    float speed = 800.f;

    float minX = 0.f;
    float maxX = 0.f;

public:
    BrickBat(const std::string& name = "BrickBat");
    ~BrickBat() = default;

    void Init() override;
    void Release() override;
    void Reset() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;

    sf::FloatRect GetGlobalBound() { return shape.getGlobalBounds(); }
};
