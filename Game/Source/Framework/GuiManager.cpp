#include "GuiManager.h"

#pragma comment( lib, "../Game/Source/External/SDL_ttf/libx86/SDL2_ttf.lib" )


GuiManager::GuiManager(Input* input, Render* render)
{
	this->input = input;
	this->render = render;
}

GuiManager::~GuiManager()
{
}

bool GuiManager::Awake()
{
	onNewLayerSet += std::bind(&GuiManager::SortLayers, this);
	creation = new ControlCreation(&controls, &config, &selectID, internalDeltaTime, &onNewLayerSet, input, render);
	return true;
}

bool GuiManager::Start() 
{
	bool ret = true;

	selectID.Clear();
	Navigation(true, KeyCode::TAB);

	return true;
}

bool GuiManager::PreUpdate(float dt)
{
	internalDeltaTime = &dt;

	controls.Iterate
	(
		[](Control* x)
		{
			if (!x->IsEnabled()) return;

			if (x->IsSelected()) x->Manipulate();
			else x->Update();
		}
	);

	// Gui Navigation Logic
	if (!config.Get(1) || !input->GetKeyDown(navigationKey))
		return true;

	NavigationLogic();

	return true;
}

bool GuiManager::Update(float dt)
{
	controls.Iterate
	(
		[](Control* x)
		{
			x->Draw();
		}
	);

	return true;
}

ControlCreation* GuiManager::CreateControl(Rect rectangle, int layer, bool dragOutside, bool anchored, Point scale, SDL_RendererFlip flip)
{
	return creation->Access(rectangle, layer, anchored, dragOutside, scale, flip);
}

void GuiManager::DestroyGuiControl(ID controlID)
{
	Control find = Control(ControlType::EMPTY_CONTROL, { 0, 0, 0, 0 }, false, false, {}, SDL_FLIP_NONE);
	find.id = controlID;
	int index = controls.Find(&find);
	if (index == -1) return;

	controls.Erase(index);
	if (controlID == selectID) selectID.Clear();
}

void GuiManager::Navigation(bool guiNavigation, KeyCode navigationKey)
{
	this->navigationKey = navigationKey;
	config.Set(1, guiNavigation);
}

void GuiManager::Debug(bool active)
{
	config.Set(0, active);
}

bool GuiManager::CleanUp()
{
	LOG("Freeing True Type fonts and library");

	controls.Clear();
	RELEASE(creation);

	return true;
}

void GuiManager::NavigationLogic()
{
	Control find = Control(ControlType::EMPTY_CONTROL, { 0, 0, 0, 0 }, false, false, {}, SDL_FLIP_NONE);
	find.id = selectID;
	int index = controls.Find(&find);

	Control* current = controls[index];
	if (index != -1 && current->state != ControlState::DISABLED)
	{
		current->state = ControlState::NORMAL;
		current->onDiselect.Invoke();
	}
	if (index == controls.Size() - 1)
	{
		selectID.Clear();
		return;
	}

	index++;
	Control* control = controls[index];
	// Add here all controls that can't be selected
	while (control->Type() == ControlType::TEXT || control->Type() == ControlType::IMAGE)
	{
		index++;
		if (index == controls.Size() - 1)
		{
			selectID.Clear();
			return;
		}
		control = controls[index];
	}
	selectID = control->Id();
	if (control->state != ControlState::DISABLED)
	{
		control->state = ControlState::SELECTED;
		control->onSelect.Invoke();
	};

}

void GuiManager::SortLayers()
{
	if (controls.Size() <= 1) return;

	controls.Sort([](Control* a, Control* b) { return a->Layer() > b->Layer(); });
}
