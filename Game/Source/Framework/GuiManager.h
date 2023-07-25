#pragma once

#include "Module.h"
#include "Input.h"

#include "Array.h"
#include "Flag.h"
#include "ID.h"
#include "ControlCreation.h"

class GuiManager : public Module
{

	friend class App;

public:

	// If layer is set to -1 it will be placed on the top
	ControlCreation* CreateControl(Rect rectangle, int layer = -1, bool dragOutside = true, bool anchored = true, Point scale = {1, 1}, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE);

	void DestroyGuiControl(ID controlID);

	/*
	Configuration function allows to modify some parts of the functionality of the gui :
	   - Allow Gui Navigation (allowGuiNav) allows user to navigate through controls using keyboard.
	   - Navigation Key (navKey) sets the key to navigate through controls. Default key = Tab Button. Using SDL_SCANCODE enum. "allowGuiNav" required to be allowed.
	*/
	void Navigation(bool allowGuiNav, KeyCode navKey);

	void Debug(bool active);

	void Clear();

private:

	GuiManager(Input* input, Render* Render);

	virtual ~GuiManager();

	bool Awake() override;

	bool Start() override;
	
	bool PreUpdate(float dt) override;

	bool Update(float dt) override;

	bool CleanUp() override;

	void NavigationLogic();

	void SortLayers();

private:

	Input* input = nullptr;
	Render* render = nullptr;

	Array<Control*> controls;
	ControlCreation* creation = nullptr;
	
	KeyCode navigationKey = KeyCode::TAB;
	ID selectID = ID(true);
	float* internalDeltaTime = nullptr;
	Action<> onNewLayerSet;

	// flag
	Flag config;

};