#include "stdafx.h"
#include "InputMgr.h"

//std::list<sf::Keyboard::Key> InputMgr::downKeys;
//std::list<sf::Keyboard::Key> InputMgr::heldKeys;
//std::list<sf::Keyboard::Key> InputMgr::upKeys;


std::list<InputType> InputMgr::downKeys;
std::list<InputType> InputMgr::heldKeys;
std::list<InputType> InputMgr::upKeys;

std::unordered_map<Axis, AxisInfo> InputMgr::axisInfoMap;

//sf::Mouse::Button InputMgr::downButton;
//sf::Mouse::Button InputMgr::upButton;

void InputMgr::Init()
{
	AxisInfo infoH;
	infoH.axis = Axis::Horizontal;
	infoH.positivies.push_back({ InputType::Type::Keyboard, static_cast<int>(sf::Keyboard::D) });
	infoH.positivies.push_back({ InputType::Type::Keyboard, static_cast<int>(sf::Keyboard::Right) });
	infoH.negativies.push_back({ InputType::Type::Keyboard, static_cast<int>(sf::Keyboard::A) });
	infoH.negativies.push_back({ InputType::Type::Keyboard, static_cast<int>(sf::Keyboard::Left) });
	axisInfoMap.insert({ Axis::Horizontal, infoH });

	AxisInfo infoV;
	infoV.axis = Axis::Vertical;
	infoV.positivies.push_back({ InputType::Type::Keyboard, static_cast<int>(sf::Keyboard::S) });
	infoV.positivies.push_back({ InputType::Type::Keyboard, static_cast<int>(sf::Keyboard::Down) });
	infoV.negativies.push_back({ InputType::Type::Keyboard, static_cast<int>(sf::Keyboard::W) });
	infoV.negativies.push_back({ InputType::Type::Keyboard, static_cast<int>(sf::Keyboard::Up) });
	axisInfoMap.insert({ Axis::Vertical, infoV });

	//InputMgr::ResetMosueButton();
}

void InputMgr::Clear() 
{
	downKeys.clear();
	upKeys.clear();
	//ResetMosueButton();
}

void InputMgr::UpdateEvent(const sf::Event& ev) 
{
	switch (ev.type)
	{
	case sf::Event::KeyPressed:
		//std::cout << "입력 한 키 값 : " << ev.key.code << std::endl;
		if (!Contains(heldKeys, { InputType::Type::Keyboard , ev.key.code }))
		{
			downKeys.push_back({ InputType::Type::Keyboard , ev.key.code });
			heldKeys.push_back({ InputType::Type::Keyboard , ev.key.code });
		}
		break;
	case sf::Event::KeyReleased:
		Remove(heldKeys, { InputType::Type::Keyboard , ev.key.code });
		upKeys.push_back({ InputType::Type::Keyboard , ev.key.code });
		break;
	case sf::Event::MouseButtonPressed:
		//std::cout << "입력 한 키 값 : " << FRAMEWORK.GetWindow().getPosition().x << std::endl;
		//std::cout << "입력 한 키 값 : " << sf::Mouse::Button::Left << std::endl;
		//std::cout << "입력 한 키 값 : " << ev.key.code << std::endl;
		// 	FRAMEWORK.GetWindow().getPosition().x;
		//downButton = ev.mouseButton.button;
		if (!Contains(heldKeys, { InputType::Type::Mouse , ev.key.code }))
		{
			downKeys.push_back({ InputType::Type::Mouse , ev.key.code });
			heldKeys.push_back({ InputType::Type::Mouse , ev.key.code });
		}
		break;
	case sf::Event::MouseButtonReleased:
		//upButton = ev.mouseButton.button;
		Remove(heldKeys, { InputType::Type::Mouse , ev.key.code });
		upKeys.push_back({ InputType::Type::Mouse , ev.key.code });
		break;
	}
}

void InputMgr::Update(float dt) 
{
	//sf::Vector2i mousePos;
	for (auto& pair : axisInfoMap) {
		AxisInfo& axisInfo = pair.second;
		float raw = GetAxisRaw(axisInfo.axis);
		float dir = raw;
		if (raw == 0.f && axisInfo.value != 0.f) {
			dir = axisInfo.value > 0.f ? -1.f : 1.f;
		}


		axisInfo.value += dir * axisInfo.senssi * dt;
		axisInfo.value = Utils::Clamp(axisInfo.value, -1.f, 1.f);

		float stophold = std::abs(dir * axisInfo.senssi * dt);
		if (raw == 0.f && std::abs(axisInfo.value) < stophold)
		{
			axisInfo.value = 0.f;
		}
	}

}

bool InputMgr::GetKeyDown(InputType key)
{
	return Contains(downKeys, key);
}

bool InputMgr::GetKeyUp(InputType key)
{
	return Contains(upKeys, key);
}

bool InputMgr::GetKey(InputType key)
{
	return Contains(heldKeys, key);
}

bool InputMgr::Contains(const std::list<sf::Keyboard::Key>& list, sf::Keyboard::Key key)
{
	return std::find(list.begin(), list.end(), key) != list.end();
}

bool InputMgr::Contains(const std::list<InputType>& list, InputType key)
{
	return std::find(list.begin(), list.end(), key) != list.end();
}

void InputMgr::Remove(std::list<sf::Keyboard::Key>& list, sf::Keyboard::Key key)
{
	list.remove(key);
}

void InputMgr::Remove(std::list<InputType>& list, InputType key)
{
	list.remove(key);
}

float InputMgr::GetAxisRaw(Axis axis)
{
	auto findIt = axisInfoMap.find(axis);
	if (findIt == axisInfoMap.end()) return 0.0f;

	const AxisInfo& axisInfo = findIt->second;

	auto it = heldKeys.rbegin();

	while (it != heldKeys.rend()) {
		InputType code = *it;
		if (Contains(axisInfo.positivies, code)) {
			return 1.f;
		}
		if (Contains(axisInfo.negativies, code)) {
			return -1.f;
		}

		++it;
	}


	return 0.0f;
}

float InputMgr::GetAxis(Axis axis)
{
	auto findIt = axisInfoMap.find(axis);
	if (findIt == axisInfoMap.end()) {
		return 0.0f;
	}

	return findIt->second.value;
}

bool InputMgr::GetMouseButtonDown(InputType key)
{
	//return downButton == key;
	return Contains(downKeys, key);
}

bool InputMgr::GetMouseButtonUp(InputType key)
{
	//return upButton == key;
	return Contains(upKeys, key);
}

bool InputMgr::GetMouseButton(InputType key)
{
	return sf::Mouse::isButtonPressed((sf::Mouse::Button)key.code);
}

//void InputMgr::ResetMosueButton()
//{
//	downButton = sf::Mouse::ButtonCount;
//	upButton = sf::Mouse::ButtonCount;
//}

sf::Vector2i InputMgr::GetMousePosition()
{
	//sf::Vector2i v2;
	//v2.x = std::abs(FRAMEWORK.GetWindow().getPosition().x - sf::Mouse::getPosition().x);
	//v2.y = std::abs(FRAMEWORK.GetWindow().getPosition().y - sf::Mouse::getPosition().y);
	return sf::Mouse::getPosition(FRAMEWORK.GetWindow());
}

