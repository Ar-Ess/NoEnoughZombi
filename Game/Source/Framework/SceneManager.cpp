#include "SceneManager.h"
#include "InitialScene.h"
#include <functional>
#include "ProgressManager.h"

SceneManager::SceneManager(Render* render, Input* input, Window* window, GuiManager* gui, AssetsManager* assets, AudioSystem* audio)
{
	this->render = render;
	this->input = input;
	this->window = window;
	this->gui = gui;
	this->assets = assets;
	this->audio = audio;

	actSet += std::bind(&SceneManager::ChangeScene, this, std::placeholders::_1);
	actAdd += std::bind(&SceneManager::PushScene  , this, std::placeholders::_1);

}

SceneManager::~SceneManager()
{
}

bool SceneManager::Awake()
{
	return true;
}

bool SceneManager::Start()
{
	bool ret = true;

	PushScene(new InitialScene());
	ChangeScene(0);
	ChangeScene(0);

	return ret;
}

bool SceneManager::Update(float dt)
{
	if (currScene < 0) return true;

	if (!scenes[currScene]->Update(dt)) !trgUpdate;

	if (!scenes[currScene]->Draw(dt)) !trgUpdate;

	if (trgChangeScene != -1) ChangeScene(trgChangeScene);

	return trgUpdate();
}

bool SceneManager::CleanUp()
{
	LOG("Freeing scene manager");

	scenes[currScene]->CleanUp();

	scenes.Clear();

	return true;
}

bool SceneManager::ChangeScene(int scene)
{
	bool ret = true;
	
	if (trgChangeScene == -1)
	{
		trgChangeScene = scene;
		return true;
	}

	trgChangeScene = -1;

	if (currScene > -1 && scene != currScene) ret = scenes[currScene]->CleanUp();

	prevScene = currScene;
	currScene = scene;

	ret = scenes[currScene]->Start();

	return ret;
}

void SceneManager::PushScene(Scene* scene)
{
	scenes.Add(scene);
	scene->actAdd = &actAdd;
	scene->actSet = &actSet;
	scene->trgSaveLoad = &trgSaveLoad;
	scene->render = render;
	scene->input = input;
	scene->assets = assets;
	scene->window = window;
	scene->gui = gui;
	scene->audio = audio;
}

void SceneManager::SaveLoad(bool save)
{
	if (!ProgressManager::Begin(save))
	{
		LOG("PROGRESS MANAGER ERROR: Could not begin the Progress Manager");
		return;
	}

	scenes.Iterate<bool>
	(
		save,
		[](Scene* scene, bool save)
		{
			if (save) scene->SaveScene();
			else scene->LoadScene();
		}
	);

	ProgressManager::End(save);

	trgSaveLoad = -1;
}
