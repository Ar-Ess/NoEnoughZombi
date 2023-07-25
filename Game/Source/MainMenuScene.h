#pragma once

#include "Scene.h"

class MainMenuScene : public Scene
{
public:

	MainMenuScene();

	~MainMenuScene() override;

	bool Start() override;

	bool Update(float dt) override;

	bool CleanUp() override;

	void SaveScene() override;

	void LoadScene() override;

};
