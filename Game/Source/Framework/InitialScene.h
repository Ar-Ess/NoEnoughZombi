#pragma once

#include "Scene.h"
#include "Easing.h"

class Text;

class InitialScene : public Scene
{
public:
	
	InitialScene();

	~InitialScene() override;

	bool Start() override;

	bool Update(float dt) override;

	bool CleanUp() override;

	void SaveScene() override;
	
	void LoadScene() override;

private:

	Text* logo = nullptr;
	Easing logoEase = Easing(EaseType::LINEAR, EaseMode::IN_OUT_MODE, 6);

};