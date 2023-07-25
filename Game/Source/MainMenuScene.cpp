#include "MainMenuScene.h"
#include "GuiManager.h"
#include "GameScene.h"

MainMenuScene::MainMenuScene()
{
}

MainMenuScene::~MainMenuScene()
{
}

bool MainMenuScene::Start()
{
	gui->Debug(true);
	PushScene(new GameScene());
	Button* b = gui->CreateControl({ 540, 330, 200, 60 })->NewButton();
	b->onClick += std::bind(&MainMenuScene::SetScene, this, Scenes::GAME_SCENE);

	return true;
}

bool MainMenuScene::Update(float dt)
{
	return true;
}

bool MainMenuScene::CleanUp()
{
	gui->Clear();
	return true;
}

void MainMenuScene::SaveScene()
{
}

void MainMenuScene::LoadScene()
{
}
