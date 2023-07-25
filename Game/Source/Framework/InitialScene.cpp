#include "InitialScene.h"
#include "GuiManager.h"
#include "AssetsManager.h"
#include "MainMenuScene.h"

InitialScene::InitialScene()
{
}

InitialScene::~InitialScene()
{
}

bool InitialScene::Start()
{
	PushScene(new MainMenuScene());
	assets->NewFont("Assets/Fonts/manaspace.regular.ttf", "FONT_01");
	logo = gui->CreateControl({ 0, 0, 1280, 720 })->NewText("NO ENOUGH ZOMBI", assets->GetFont("FONT_01"), 42, Alignment::CENTER);
	logo->normalColor.a = 1;
	logo->Set();
	logoEase.onEnd += std::bind(&InitialScene::SetScene, this, Scenes::MAIN_MENU_SCENE);

	return true;
}

bool InitialScene::Update(float dt)
{
	logo->normalColor.a = logoEase.Ease(2, 255, dt);
	logo->Set();

	return true;
}

bool InitialScene::CleanUp()
{
	gui->Clear();
	return true;
}

void InitialScene::SaveScene()
{
}

void InitialScene::LoadScene()
{
}
