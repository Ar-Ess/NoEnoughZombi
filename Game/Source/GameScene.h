#pragma once

#include "Scene.h"

class Texture;

class GameScene : public Scene
{
public:

	GameScene();

	~GameScene() override;

	bool Start() override;

	bool Update(float dt) override;

	bool CleanUp() override;

	void SaveScene() override;

	void LoadScene() override;

private:

	void UpdateGame();

	void DrawGame();

private:

	Texture* garden = nullptr;

};
