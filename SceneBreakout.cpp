#include "stdafx.h"
#include "SceneBreakout.h"
#include "BrickBat.h"
#include "BallBreakout.h"
#include "Brick.h"
#include "SceneMgr.h"
#include "Framework.h"
#include "UiHud.h"

SceneBreakout::SceneBreakout()
    : Scene(SceneIds::Breakout)
{
}

void SceneBreakout::Init()
{
    fontIds.push_back("fonts/DS-DIGIT.ttf");

    bat = (BrickBat*)AddGameObject(new BrickBat("BrickBat"));

    UiHud* hud = (UiHud*)AddGameObject(new UiHud());
    ball = (BallBreakout*)AddGameObject(new BallBreakout(hud));
    ball->SetBat(bat);


    Scene::Init();

    int rows = 6;
    int cols = 12;  
    float spacingX = 10.f;
    float spacingY = 10.f;
    sf::Vector2f brickSize = { 80.f, 25.f };  

    float totalWidth = cols * brickSize.x + (cols - 1) * spacingX;

    float startX = (FRAMEWORK.GetWindowSize().x - totalWidth) * 0.5f + 35.f;
    float startY = 100.f;

    for (int y = 0; y < rows; ++y)
    {
        for (int x = 0; x < cols; ++x)
        {
            Brick* brick = new Brick();
            brick->Init();
            brick->SetSize(brickSize);
            float posX = startX + x * (brickSize.x + spacingX);
            float posY = startY + y * (brickSize.y + spacingY);
            brick->SetPosition({ posX, posY });
            brick->Reset();
            AddGameObject(brick);
            bricks.push_back(brick);
        }
    }


}

void SceneBreakout::Enter()
{
    isClear = false;
    ballLaunched = false;

    Reset();
    Scene::Enter();
}

void SceneBreakout::Reset()
{
    bat->Reset();
    ball->Reset();

    for (Brick* b : bricks)
    {
        if (b != nullptr)
            b->Reset(); 
    }
}

void SceneBreakout::Update(float dt)
{

    Scene::Update(dt);

    if (InputMgr::GetKeyDown({ InputType::Type::Keyboard, sf::Keyboard::BackSpace })) {
        SCENE_MGR.ChangeScene(SceneIds::SelectGame);
    }

    if (!ballLaunched)
    {
        ball->SetPosition(bat->GetPosition() - sf::Vector2f(0.f, 20.f));

        if (InputMgr::GetKeyDown({ InputType::Type::Keyboard, sf::Keyboard::Space }))
        {
            sf::Vector2f dir(1.f, -1.f);
            Utils::Normalize(dir);
            ball->Fire(dir, 400.f);
            ballLaunched = true;
        }
    }

    if (ballLaunched)
    {
        /*std::cout << "Ball Bounds: " << ball->GetGlobalBounds().left << ", "
          << ball->GetGlobalBounds().top << ", "
          << ball->GetGlobalBounds().width << ", "
          << ball->GetGlobalBounds().height << std::endl;*/
        for (auto& b : bricks)
        {
            if (!b->IsDestroyed() &&
                b->GetGlobalBounds().intersects(ball->getShape().getGlobalBounds()))
            {
                b->Destroy();
                ball->BounceVertically();
                break;
            }
        }
    }

    bool allDestroyed = std::all_of(
        bricks.begin(), bricks.end(),
        [](Brick* br) { return br->IsDestroyed(); });

    if (allDestroyed && !isClear)
    {
        isClear = true;
    }
}

void SceneBreakout::Draw(sf::RenderWindow& window)
{
    Scene::Draw(window);

    if (isClear)
    {
        sf::Font font;
        font.loadFromFile("fonts/DS-DIGIT.ttf");
        sf::Text text("CLEAR", font, 100);
        text.setFillColor(sf::Color::Yellow);
        text.setPosition(FRAMEWORK.GetWindowSize().x / 2.f - text.getLocalBounds().width / 2, FRAMEWORK.GetWindowSize().y / 2.f - text.getLocalBounds().height / 2);
        window.draw(text);
    }
}