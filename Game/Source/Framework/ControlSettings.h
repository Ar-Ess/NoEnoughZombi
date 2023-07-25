#pragma once

#include "GuiControl.h"
#include "Alignment.h"

class ControlSettings
{
public:
	ControlSettings()
	{
	}

	Alignment AddGuiString(const char* text, unsigned int fontIndex = 0, SDL_Color color = { 0, 0, 0, 255 })
	{
		// You already created a text for this Gui Control, no more that 1 text is allowed
		assert(control->type != ControlType::TEXT && control->text == nullptr);

		control->text = new GuiString(control->bounds, text, fontIndex, control->id, control->scale, control->render, control->gui, control->tex, control->anchored, color);

		return Alignment(control, Point{ control->bounds.w, control->bounds.h }, this);
	}

	// SliderSettings function allows to modify some parts of the functionality of a slider:
	//   - Initial Value: Set an initial value in which the slider will start
	//   - Allow RIPS: this system stands for "Retrieve Information Pressed State". If this option is false, 
	//                    the slider will retieve the value when the the click button is released. If the option
	//                    it true, it will retrieve the value each frame that the slider is pressed.
	//   - Range: this variable allows to set the value given at the minimum position and the value given at the
	//            maximum position of the slider. Point{minimum, maximum}
	//   - Keys: 
	ControlSettings* SliderSettings(float initValue = 0.0f, bool allowRIPS = false, Point range = { 0, 100.0f }, unsigned int subsKey = 80, unsigned int addKey = 79, unsigned int slowKey = 225)
	{
		// You tried to modify slider setting in another gui control. SliderSettings is only for Sliders
		assert(control->type == ControlType::SLIDER);

		GuiSlider* slider = (GuiSlider*)control;
		slider->SetRIPS(allowRIPS);
		slider->SetInitialValue(initValue);
		slider->SetRange(range);
		slider->SetKeys(subsKey, addKey, slowKey);

		return this;
	}

	ControlSettings* TextSettings(const char* text = "", SDL_Color color = { 255, 255, 255, 255 })
	{
		// You tried to modify slider setting in another gui control. SliderSettings is only for Sliders
		assert(control->type == ControlType::TEXT);

		GuiString* string = (GuiString*)control;
		string->SetString(text, color);

		return this;
	}


private:

	Control* control = nullptr;
};
