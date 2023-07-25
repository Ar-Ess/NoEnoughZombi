#include "Slider.h"
#include "Maths.h"

Slider::Slider(Rect rectangle, Rect slider, Point range, float initialValue, float percent, bool anchored, bool dragOutside, Point scale, SDL_RendererFlip flip) :
	Control(ControlType::SLIDER, rectangle, anchored, dragOutside, scale, flip)
{
	this->slider = slider;
	this->range = range;
    this->percent = percent;
    this->slider.Position({rectangle.x, rectangle.y + (rectangle.h / 2)}, Alignment::CENTER);
    initialSliderX = slider.x;
    this->Value(initialValue);
}

Slider::~Slider()
{
}

void Slider::Value(float value)
{
	value = Maths::Clamp(value, range.x, range.y);
    float distance = range.y - range.x;
    value -= range.x;
    value /= distance;
    float positionOffset = rectangle.w * value;
    slider.x = rectangle.x + positionOffset;
}

float Slider::Value()
{
    float sliderPosition = slider.Position(Alignment::CENTER).x - rectangle.x;
    float value = sliderPosition / rectangle.w;
	return (value * range.y) + range.x;
}

bool Slider::Update()
{
    Point mouse = input->GetMousePosition();
    bool on = Maths::CheckCollision(Rect{ mouse, 1.0f, 1.0f }, { slider.Position(), slider.Size().Multiply(scale) });
    bool click = (input->GetMouseButton(MouseCode::BUTTON_LEFT));
    static float prevSliderX = slider.x;

    switch (state)
    {
    case ControlState::NORMAL:
        state = ControlState::NORMAL;
        if (!on) break;
        state = ControlState::FOCUSED;
        onFocus.Invoke();
        [[fallthrough]];

    case ControlState::FOCUSED:
        if (!on)
        {
            state = ControlState::NORMAL;
            onUnfocus.Invoke();
            break;
        }
        if (!click) break;
        state = ControlState::PRESSED;
        onClick.Invoke();
        mouseOffset = mouse.x - slider.Position(Alignment::CENTER).x;
        initialSliderX = slider.x;
        [[fallthrough]];

    case ControlState::PRESSED:
        if (!on && !dragOutside)
        {
            state = ControlState::NORMAL;
            onRemove.Invoke();
            break;
        }

        slider.Position({ mouse.x - mouseOffset, slider.y + (slider.h / 2) }, Alignment::CENTER);
        slider.x = Maths::Clamp(slider.x, rectangle.x - (slider.w/2), rectangle.x + rectangle.w - (slider.w / 2));

        if (click)
        {
            if (slider.x != prevSliderX) onValueChangedRuntime.Invoke(Value());
            prevSliderX = slider.x;
            break;
        }
        else
        {
            if (on) state = ControlState::FOCUSED;
            else state = ControlState::NORMAL;
            if (slider.x != prevSliderX) onValueChangedRuntime.Invoke(Value());
        }

        prevSliderX = slider.x;
        if (slider.x != initialSliderX)
        {
            onValueChanged.Invoke(Value());
        }
        onRelease.Invoke();
        break;
    }

    return true;
}

bool Slider::Draw() const
{
    Texture* trailTexture = nullptr;
    Texture* sliderTexture = nullptr;

    switch (state)
    {
    case ControlState::DISABLED: 
        trailTexture = texBarDisabled; 
        sliderTexture = texSliderDisabled; 
        break;
    case ControlState::NORMAL: 
        trailTexture = texBarNormal;   
        sliderTexture = texSliderNormal;   
        break;
    case ControlState::FOCUSED: 
        trailTexture = texBarFocused;  
        sliderTexture = texSliderFocused;  
        break;
    case ControlState::PRESSED: 
        trailTexture = texBarPressed;  
        sliderTexture = texSliderPressed;  
        break;
    case ControlState::SELECTED: 
        trailTexture = texBarSelected; 
        sliderTexture = texSliderSelected; 
        break;
    }

    render->DrawTexture(trailTexture, rectangle.Position(), scale, anchored, nullptr, 0, flip);
    render->DrawTexture(sliderTexture, rectangle.Position(), scale, anchored, nullptr, 0, flipSlider);

    if (!config->Get(0)) return true;

    switch (state)
    {
    case ControlState::DISABLED: 
        render->DrawRectangle(rectangle, { 100, 100, 100, 80 }, {}, { 1, 1 }, anchored);
        render->DrawRectangle(slider,    { 150, 100, 100, 80 }, {}, { 1, 1 }, anchored); 
        break;
    case ControlState::NORMAL:   
        render->DrawRectangle(rectangle, { 0, 255,   0, 80 }, {}, { 1, 1 }, anchored);
        render->DrawRectangle(slider,    { 0, 200,   0, 80 }, {}, { 1, 1 }, anchored); 
        break;
    case ControlState::FOCUSED:  
        render->DrawRectangle(rectangle, { 255, 255,   0, 80 }, {}, { 1, 1 }, anchored);
        render->DrawRectangle(slider,    { 255, 255, 70, 80 }, {}, { 1, 1 }, anchored); 
        break;
    case ControlState::PRESSED:  
        render->DrawRectangle(rectangle, { 0, 255, 255, 80 }, {}, { 1, 1 }, anchored);
        render->DrawRectangle(slider,    { 0, 200, 200, 80 }, {}, { 1, 1 }, anchored); 
        break;
    case ControlState::SELECTED: 
        render->DrawRectangle(rectangle, { 100, 100, 255, 80 }, {}, { 1, 1 }, anchored);
        render->DrawRectangle(slider,    { 150, 150, 255, 80 }, {}, { 1, 1 }, anchored);
        break;
    }

    return true;
}

bool Slider::Manipulate()
{
    if (Maths::CheckCollision(Rect{ input->GetMousePosition(), 1.0f, 1.0f }, { slider.Position(), slider.Size().Multiply(scale) })
        && input->GetMouseButtonDown(MouseCode::BUTTON_LEFT))
    {
        onClick.Invoke();
        state = ControlState::PRESSED;
        mouseOffset = input->GetMousePosition().x - slider.Position(Alignment::CENTER).x;
        initialSliderX = slider.x;
        (*selectID).Clear();
        return false;
    }

    if (input->GetKeyDown(augmentKey))
    {
        slider.x += rectangle.w * percent;
        slider.x = Maths::Clamp(slider.x, rectangle.x - (slider.w / 2), rectangle.x + rectangle.w - (slider.w / 2));
        onValueSubmitted.Invoke(Value());
    }

    if (input->GetKeyDown(decreaseKey))
    {
        slider.x -= rectangle.w * percent;
        slider.x = Maths::Clamp(slider.x, rectangle.x - (slider.w / 2), rectangle.x + rectangle.w - (slider.w / 2));
        onValueSubmitted.Invoke(Value());
    }

    return true;
}
