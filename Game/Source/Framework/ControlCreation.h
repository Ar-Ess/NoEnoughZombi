#pragma once

#include "Array.h"
#include "Flag.h"
#include "Button.h"
#include "Image.h"
#include "Slider.h"
#include "Checkbox.h"
#include "Text.h"
#include "Maths.h"


class ControlCreation
{
public:

	Button* NewButton()
	{
		Control* control = new Button(rectangle, anchored, dragOutside, scale, flip);
		controls->Add(control);
		SetModules(control);
		return (Button*)control;
	}

	Checkbox* NewCheckbox(bool check = false)
	{
		Control* control = new Checkbox(rectangle, check, anchored, dragOutside, scale, flip);
		controls->Add(control);
		SetModules(control);
		return (Checkbox*)control;
	}

	Text* NewText(const char* text, Font* font = nullptr, int size = -1, Alignment align = Alignment::TOP_LEFT)
	{
		Control* control = new Text(rectangle, text, align, scale, anchored, flip);
		controls->Add(control);
		SetModules(control);
		((Text*)control)->Set(nullptr, font, size);
		return (Text*)control;
	}
	
	// percent is a value clamped from 0 to 1. Is the % of value increment when manipulating the slider while navigating
	Slider* NewSlider(Rect slider, Point range, float initialValue = 0, float percent = 0.1f)
	{
		if (Maths::Max(range.x, range.y) == range.x)
		{
			float yy = range.y;
			range.y = range.x;
			range.x = yy;
		}
		percent = Maths::Clamp(percent, 0, 1);
		Control* control = new Slider(rectangle, slider, range, initialValue, percent, anchored, dragOutside, scale, flip);
		controls->Add(control);
		SetModules(control);
		return (Slider*)control;
	}

	Image* NewImage(Texture* texture)
	{
		Control* control = new Image(rectangle, texture, scale, anchored, flip);
		controls->Add(control);
		SetModules(control);
		return (Image*)control;
	}

private:

	friend class GuiManager;

	void SetModules(Control* control)
	{
		control->SetModules(config, selectID, dt, input, render);
		control->onNewLayerSet = onNewLayerSet;
		layer == -1 ? control->layer = controls->At(controls->Size() - 1)->layer + 1 : control->Layer(layer); 
	}

	ControlCreation* Access(Rect rectangle, int layer, bool anchored, bool dragOutside, Point scale, SDL_RendererFlip flip)
	{
		this->rectangle = rectangle;
		this->anchored = anchored;
		this->scale = scale;
		this->dragOutside = dragOutside;
		this->flip = flip;
		this->layer = layer;

		return this;
	}

	ControlCreation(Array<Control*>* controls, Flag* config, ID* selectID, float* dt, Action<>* onNewLayerSet, Input* input, Render* render)
	{
		this->controls = controls;
		this->config = config;
		this->input = input;
		this->render = render;
		this->selectID = selectID;
		this->dt = dt;
		this->onNewLayerSet = onNewLayerSet;
	}

private:

	Array<Control*>* controls = nullptr;
	Flag* config = nullptr;
	ID* selectID = nullptr;
	Input* input = nullptr;
	Render* render = nullptr;
	float* dt = nullptr;
	Rect rectangle = {};
	bool anchored = true;
	bool dragOutside = true;
	Point scale = {};
	SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE;
	Action<>* onNewLayerSet = nullptr;
	int layer = -1;
};
