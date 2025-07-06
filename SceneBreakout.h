#pragma once
#include "Scene.h"


class Brick;
class BallBreakout;
class BrickBat;

class SceneBreakout : public Scene
{
protected:
    BrickBat* bat = nullptr;
    BallBreakout* ball = nullptr;
    std::vector<Brick*> bricks;

    float launchedTimer = 0.f;
    bool ballLaunched = false;
    bool isClear = false;

public:
    SceneBreakout();
    ~SceneBreakout() override = default;

    void Init() override;
    void Enter() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;

    void Reset();
};

