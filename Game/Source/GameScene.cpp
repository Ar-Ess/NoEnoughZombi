#include "GameScene.h"
#include "GuiManager.h"
#include "Render.h"
#include "AssetsManager.h"
#include "Tile.h"

#define TILE_SIZE 112
#define TILE_W_COUNT 9
#define TILE_H_COUNT 5

GameScene::GameScene()
{
	grid = new Grid<Tile*>(TILE_W_COUNT, TILE_H_COUNT);
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
	grid->CleanUp();
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
	render->DrawGrid({ 150, 130, TILE_SIZE * TILE_W_COUNT, TILE_SIZE * TILE_H_COUNT }, { TILE_W_COUNT, TILE_H_COUNT }, {255, 255, 255, 230});

	for (unsigned int i = 0; i < grid->Size(); ++i) (*grid)[i]->Draw(true);

}
