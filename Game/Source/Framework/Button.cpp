#include "Button.h"
#include "Maths.h"

Button::Button(Rect rectangle, bool anchored, bool dragOutside, Point scale, SDL_RendererFlip flip) :
    Control(ControlType::BUTTON, rectangle, anchored, dragOutside, scale, flip)
{
}

Button::~Button()
{
}

bool Button::Update()
{
    Point mouse = input->GetMousePosition();
    bool on = Maths::CheckCollision(Rect{ mouse, 1.0f, 1.0f }, { rectangle.Position(), rectangle.Size().Multiply(scale) });
    bool click = (input->GetMouseButton(MouseCode::BUTTON_LEFT));

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
        [[fallthrough]];

    case ControlState::PRESSED:
        if (!on && !dragOutside)
        {
            state = ControlState::NORMAL;
            onRemove.Invoke();
            break;
        }
        if (click) break;
        if (on) state = ControlState::FOCUSED;
        else state = ControlState::NORMAL;
        onRelease.Invoke();
        break;
    }

    return true;
}

bool Button::Draw() const
{
    Texture* texture = nullptr;
    switch (state)
    {
    case ControlState::DISABLED: texture = texDisabled; break;
    case ControlState::NORMAL: texture   = texNormal;   break;
    case ControlState::FOCUSED: texture  = texFocused;  break;
    case ControlState::PRESSED: texture  = texPressed;  break;
    case ControlState::SELECTED: texture = texSelected; break;
    }

    render->DrawTexture(texture, rectangle.Position(), scale, anchored, nullptr, 0, flip);

    if (!config->Get(0)) return true;

    switch (state)
    {
    case ControlState::DISABLED: render->DrawRectangle(rectangle, { 100, 100, 100, 80 }, {}, { 1, 1 }, anchored); break;
    case ControlState::NORMAL:   render->DrawRectangle(rectangle, {   0, 255,   0, 80 }, {}, { 1, 1 }, anchored); break;
    case ControlState::FOCUSED:  render->DrawRectangle(rectangle, { 255, 255,   0, 80 }, {}, { 1, 1 }, anchored); break;
    case ControlState::PRESSED:  render->DrawRectangle(rectangle, {   0, 255, 255, 80 }, {}, { 1, 1 }, anchored); break;
    case ControlState::SELECTED: render->DrawRectangle(rectangle, { 100, 100, 255, 80 }, {}, { 1, 1 }, anchored); break;
    }

    return true;
}

bool Button::Manipulate()
{
    if (Maths::CheckCollision(Rect{ input->GetMousePosition(), 1.0f, 1.0f }, { rectangle.Position(), rectangle.Size().Multiply(scale) })
        && input->GetMouseButtonDown(MouseCode::BUTTON_LEFT))
    {
        onClick.Invoke();
        state = ControlState::PRESSED;
        (*selectID).Clear();
        return false;
    }

    if (input->GetKeyDown(submitKey)) onSubmit.Invoke();

    return true;
}
