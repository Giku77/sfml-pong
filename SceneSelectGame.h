#pragma once
#include "Scene.h"
class SceneSelectGame : public Scene
{
protected:
    enum class GameChoice { PingPong, Breakout };
    GameChoice currentChoice = GameChoice::PingPong;

    sf::Text titleText;
    sf::Text pongText;
    sf::Text breakoutText;
    sf::Font font;

    sf::Texture pongTexture;
    sf::Texture breakoutTexture;
    sf::Sprite pongSprite;
    sf::Sprite breakoutSprite;

public:
    SceneSelectGame();
    virtual void Init() override;
    virtual void Update(float dt) override;
    virtual void Draw(sf::RenderWindow& window) override;
};

