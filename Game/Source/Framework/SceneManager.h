#pragma once

#include "Module.h"
#include "Scene.h"
#include "Array.h"
#include "Action.h"
#include "Trigger.h"

class SceneManager : public Module
{

	friend class App;

private:

	SceneManager(Render* render, Input* input, Window* window, GuiManager* gui, AssetsManager* assets, AudioSystem* audio);
	
	virtual ~SceneManager();

	bool Awake() override;

	bool Start() override;

	bool Update(float dt) override;

	bool CleanUp() override;

	bool ChangeScene(int scene);

	void PushScene(Scene* scene);

	void SaveLoad(bool save);

private:

	int currScene = -1;
	int prevScene = -1;

	Render* render = nullptr;
	Input* input = nullptr;
	GuiManager* gui = nullptr;
	AssetsManager* assets = nullptr;
	Window* window = nullptr;
	AudioSystem* audio = nullptr;

	Array<Scene*> scenes;

	Action<int> actSet;
	Action<Scene*> actAdd;

	Trigger trgUpdate;

	int trgSaveLoad = -1;
	int trgChangeScene = -1;

};