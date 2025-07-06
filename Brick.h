#pragma once
#include "GameObject.h"

class Brick : public GameObject
{
protected:
    sf::RectangleShape shape;
    bool isDestroyed = false;

public:
    Brick();
    void Init() override;
    void Reset() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;

    void Destroy();
    bool IsDestroyed() const { return isDestroyed; }

    const sf::RectangleShape& getShape() const { return shape; }

    const sf::FloatRect& GetGlobalBounds() const { return shape.getGlobalBounds(); }

    void SetPosition(const sf::Vector2f& pos);
    void SetSize(const sf::Vector2f& size);
    void SetColor(const sf::Color& color);

    void Release() override;
};
