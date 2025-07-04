#pragma once
#include "GameObject.h"
class Bat :
    public GameObject
{
protected:
    sf::RectangleShape shape;
    sf::RectangleShape shape2;

    float speed = 800.f;
    sf::Vector2f dir;
    sf::Vector2f dir2;

    float minX = 0.f, maxX = 0.f;

public:
    Bat(const std::string& name = "");
    ~Bat() = default;

    void SetRotation(float rot)  override;
    void SetPosition(const sf::Vector2f& pos) override;
    void SetScale(const sf::Vector2f& s) override;
    void SetOrigin(const sf::Vector2f& o) override;
    void SetOrigin(Origins preset) override;

    void Init() override;
    void Release() override;
    void Reset() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;

    sf::FloatRect GetGlobalBound() { return shape.getGlobalBounds(); }
    sf::FloatRect GetGlobalBound2() { return shape2.getGlobalBounds(); }
};

