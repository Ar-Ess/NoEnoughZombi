#include "GameScene.h"
#include "GuiManager.h"
#include "Render.h"
#include "AssetsManager.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

bool GameScene::Start()
{
	assets->NewTexture("Assets/Textures/garden_demo.png", "GARDEN_DEMO");
	garden = assets->GetTexture("GARDEN_DEMO");

	return true;
}

bool GameScene::Update(float dt)
{
	UpdateGame();

	DrawGame();

	return true;
}

bool GameScene::CleanUp()
{
	gui->Clear();
	return true;
}

void GameScene::SaveScene()
{
}

void GameScene::LoadScene()
{
}

void GameScene::UpdateGame()
{
}

void GameScene::DrawGame()
{

	render->DrawTexture(garden, {}, {1, 1});
	//render->DrawGrid();

}
