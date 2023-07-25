#pragma once

#include "Control.h"

class Slider : public Control
{

	friend class ControlCreation;

public:

    virtual ~Slider();

    void Value(float value);

    float Value();

private:

    // Percent is a value that goes from 0 to 1. It means the percentage of the range it will upgrade with the movement
    Slider(Rect rectangle, Rect slider, Point range, float initialValue, float percent, bool anchored, bool dragOutside, Point scale, SDL_RendererFlip flip);
    
    bool Update() override;

    bool Draw() const override;

    bool Manipulate() override;

public:

    // Set the key to augment with the slider when selected
    KeyCode augmentKey = KeyCode::RIGHT;
    // Set the key to decrease with the slider when selected
    KeyCode decreaseKey = KeyCode::LEFT;
    // Set the key to slow the percent of slider movement
    KeyCode focusKey = KeyCode::LEFT;
    // Calls when the user releases the click button
    Action<> onRelease;
    // Calls when the user removes the pointer from the button while clicking. This won't call if DGSO enabled
    Action<> onRemove;
    // Calls when the user puts the mouse on the button
    Action<> onFocus;
    // Calls when the user puts the mouse on the button
    Action<> onUnfocus;
    // Calls when the user submits or clicks on the button.
    Action<> onClick;
    // Calls when the value of the slider has changed
    Action<float> onValueChanged;
    // Calls when the value of the slider is changing
    Action<float> onValueChangedRuntime;
    // Calls when the value of the slider has changed when it was selected
    Action<float> onValueSubmitted;

    Texture* texBarDisabled = nullptr;
    Texture* texBarNormal = nullptr;
    Texture* texBarFocused = nullptr;
    Texture* texBarPressed = nullptr;
    Texture* texBarSelected = nullptr;
    Texture* texSliderDisabled = nullptr;
    Texture* texSliderNormal = nullptr;
    Texture* texSliderFocused = nullptr;
    Texture* texSliderPressed = nullptr;
    Texture* texSliderSelected = nullptr;

    SDL_RendererFlip flipSlider = SDL_RendererFlip::SDL_FLIP_NONE;

private:

    Rect slider;
    Point range = { 0, 1 };
    float percent = 0.1f;

    float mouseOffset = 0;
    float initialSliderX = 0;

};