#include "stdafx.h"
#include "UiHud.h"

UiHud::UiHud(const std::string& name)
{
}


void UiHud::SetMsg(const std::string& msg)
{
	textMsg.setString(msg);
	Utils::SetOrigin(textMsg, Origins::MC);
}

void UiHud::Init()
{
	fontId = "fonts/DS-DIGIT.ttf";

	//textMsg.setString("Press Enter to start!");
	textMsg.setCharacterSize(100);
	textMsg.setFillColor(sf::Color::White);
	textMsg.setPosition(FRAMEWORK.GetWindowSize().x * 0.5f, FRAMEWORK.GetWindowSize().y * 0.5f);

}

void UiHud::Release()
{
}

void UiHud::Reset()
{
	textMsg.setFont(FONT_MGR.Get(fontId));

	//isShowMsg = true;
	//SetMsg("MSG!");
}

void UiHud::Update(float dt)
{
}

void UiHud::Draw(sf::RenderWindow& window)
{
	std::cout << "showMsg : " << isShowMsg << std::endl;
	if (isShowMsg) window.draw(textMsg);
}
