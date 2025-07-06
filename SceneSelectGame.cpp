#include "stdafx.h"
#include "SceneSelectGame.h"
#include "SceneMgr.h"

SceneSelectGame::SceneSelectGame()
    : Scene(SceneIds::SelectGame)
{
}

void SceneSelectGame::Init()
{
    font.loadFromFile("fonts/DS-DIGIT.ttf");

    sf::FloatRect windowBounds = FRAMEWORK.GetWindowBounds();
    sf::Vector2f windowCenter = { windowBounds.width * 0.5f, windowBounds.height * 0.5f };

    titleText.setFont(font);
    titleText.setString("BALL GAME");
    titleText.setCharacterSize(120);

    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.width * 0.5f, titleBounds.height * 0.5f);
    titleText.setPosition(windowCenter.x, 50.f);

    pongText.setFont(font);
    pongText.setString("1. PING - PONG");
    pongText.setCharacterSize(40);
    sf::FloatRect pongBounds = pongText.getLocalBounds();
    pongText.setOrigin(pongBounds.width * 0.5f, pongBounds.height * 0.5f);
    pongText.setPosition(windowCenter.x - 150.f, windowCenter.y + 130.f);

    breakoutText.setFont(font);
    breakoutText.setString("2. BREAKOUT");
    breakoutText.setCharacterSize(40);
    sf::FloatRect breakoutBounds = breakoutText.getLocalBounds();
    breakoutText.setOrigin(breakoutBounds.width * 0.5f, breakoutBounds.height * 0.5f);
    breakoutText.setPosition(windowCenter.x + 150.f, windowCenter.y + 130.f);


    pongTexture.loadFromFile("images/1.png");      
    pongSprite.setTexture(pongTexture);
    pongSprite.setScale(0.5f, 0.5f);

    breakoutTexture.loadFromFile("images/2.png");
    breakoutSprite.setTexture(breakoutTexture);
    breakoutSprite.setScale(0.5f, 0.5f);

    pongSprite.setPosition(
        pongText.getPosition().x - pongSprite.getGlobalBounds().width * 0.5f,
        pongText.getPosition().y - pongText.getCharacterSize() - pongSprite.getGlobalBounds().height
    );

    breakoutSprite.setPosition(
        breakoutText.getPosition().x - breakoutSprite.getGlobalBounds().width * 0.5f,
        breakoutText.getPosition().y - breakoutText.getCharacterSize() - breakoutSprite.getGlobalBounds().height
    );

}

void SceneSelectGame::Update(float dt)
{
    // 좌우 방향 입력
    if (InputMgr::GetKeyDown({ InputType::Type::Keyboard, sf::Keyboard::Left }))
        currentChoice = GameChoice::PingPong;

    if (InputMgr::GetKeyDown({ InputType::Type::Keyboard, sf::Keyboard::Right }))
        currentChoice = GameChoice::Breakout;

    // 엔터 입력으로 씬 이동
    if (InputMgr::GetKeyDown({ InputType::Type::Keyboard, sf::Keyboard::Enter }))
    {
        if (currentChoice == GameChoice::PingPong)
        {
            SCENE_MGR.ChangeScene(SceneIds::Game);
        }
        else
        {
            SCENE_MGR.ChangeScene(SceneIds::Breakout); 
        }
    }

    pongText.setFillColor(currentChoice == GameChoice::PingPong ? sf::Color::Yellow : sf::Color::White);
    breakoutText.setFillColor(currentChoice == GameChoice::Breakout ? sf::Color::Yellow : sf::Color::White);
}

void SceneSelectGame::Draw(sf::RenderWindow& window)
{
    window.draw(pongSprite);
    window.draw(breakoutSprite);
    window.draw(titleText);
    window.draw(pongText);
    window.draw(breakoutText);
}