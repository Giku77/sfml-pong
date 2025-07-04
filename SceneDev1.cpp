#include "stdafx.h"
#include "SceneDev1.h"
#include "TextGo.h"

SceneDev1::SceneDev1()
	: Scene(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{
	fontIds.push_back("fonts/DS-DIGIT.ttf");

	TextGo* go = new TextGo("fonts/DS-DIGIT.ttf");
	go->SetString("Dev 1");
	go->SetCharacterSize(30);
	go->SetFillColor(sf::Color::White);
	AddGameObject(go);

	textGo = new TextGo("fonts/DS-DIGIT.ttf");
	textGo->SetString("Dev 1");
	textGo->SetCharacterSize(30);
	textGo->SetFillColor(sf::Color::Red);
	AddGameObject(textGo);

	Scene::Init();
}

void SceneDev1::Update(float dt)
{
	if (InputMgr::GetKeyDown({ InputType::Type::Keyboard, (int)sf::Keyboard::Space }))
	{
		SCENE_MGR.ChangeScene(SceneIds::Dev2);
	}

	if (InputMgr::GetKeyDown({ InputType::Type::Keyboard, (int)sf::Keyboard::Num1 }))
	{
		textGo->sortingOrder = -1;
	}

	if (InputMgr::GetKeyDown({ InputType::Type::Keyboard, (int)sf::Keyboard::Num2 }))
	{
		textGo->sortingOrder = 1;
	}

	sf::Vector2f dir;
	dir.x = InputMgr::GetAxisRaw(Axis::Horizontal);
	dir.y = InputMgr::GetAxisRaw(Axis::Vertical);

	sf::Vector2f pos = textGo->GetPosition();
	pos += dir * 100.f * dt;
	textGo->SetPosition(pos);

	/*InputMgr::GetMouseButtonDown(sf::Mouse::Button key)
	InputMgr::GetMouseButtonUp(sf::Mouse::Button key)
	InputMgr::GetMouseButton(sf::Mouse::Button key)
    sf::Vector2i InputMgr::GetMousePosition()*/
	if (InputMgr::GetMouseButtonDown({ InputType::Type::Mouse, (int)sf::Mouse::Left })) {
		std::cout << "왼쪽 마우스 클릭 다운" << std::endl;
		std::cout << "마우스 좌표 : " << InputMgr::GetMousePosition().x << ", " << InputMgr::GetMousePosition().y << std::endl;
	}
	if (InputMgr::GetMouseButtonDown({ InputType::Type::Mouse, (int)sf::Mouse::Right })) {
		std::cout << "오른쪽 마우스 클릭 업" << std::endl;
	}
	if (InputMgr::GetMouseButtonDown({ InputType::Type::Mouse, (int)sf::Mouse::Middle })) {
		std::cout << "중간 마우스 클릭" << std::endl;
	}
}
