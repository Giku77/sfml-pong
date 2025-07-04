#pragma once
#include "Scene.h"

class TextGo;

class SceneDev1 : public Scene
{
protected:
	TextGo* textGo;
public:
	SceneDev1();

	void Init() override;
	void Update(float dt) override;
};

