#pragma once
#include "GameObject.h"
class UiHud :
    public GameObject
{
protected:
    sf::Text textMsg;

    std::string fontId;
    bool isShowMsg = false;


public:
    UiHud(const std::string& name = "");
    ~UiHud() override = default;

    void SetMsg(const std::string& msg);
    void SetShowMsg(bool show) { isShowMsg = show; }
    
    void Init() override;

    void Release() override;

    void Reset() override;

    void Update(float dt) override;

    void Draw(sf::RenderWindow& window) override;

};

