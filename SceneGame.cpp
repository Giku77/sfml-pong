#include "stdafx.h"
#include "SceneGame.h"
#include "Bat.h"
#include "Ball.h"
#include "UiHud.h"

SceneGame::SceneGame()
	:Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	fontIds.push_back("fonts/DS-DIGIT.ttf");

	bat = (Bat*)AddGameObject(new Bat("Bat"));
	UiHud* hud = (UiHud*)AddGameObject(new UiHud());
	ball = (Ball*)AddGameObject(new Ball(hud));
	ball->setBat(bat);
	Scene::Init();
}

void SceneGame::Enter()
{
	ballActvie = false;

	Scene::Enter();
}

void SceneGame::Update(float dt) {
	Scene::Update(dt);

	if (InputMgr::GetKeyDown({ InputType::Type::Keyboard, sf::Keyboard::BackSpace })) {
		SCENE_MGR.ChangeScene(SceneIds::SelectGame);
	}

	if (!ballActvie) {
		ball->SetPosition(bat->GetPosition());

		if (InputMgr::GetKeyDown({ InputType::Type::Keyboard, sf::Keyboard::Space })) {
			ballActvie = true;

			sf::Vector2f dir(1.f, Utils::RandomValue() > 0.5f ? 1.f : -1.f);
			Utils::Normalize(dir);
			ball->Fire(dir, 500.f);
		}
	}
}

void SceneGame::SetGameOver()
{
	SCENE_MGR.ChangeScene(SCENE_MGR.GetCurrentSceneId());
}
