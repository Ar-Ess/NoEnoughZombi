#include "Checkbox.h"
#include "Maths.h"

Checkbox::Checkbox(Rect rectangle, bool check, bool anchored, bool dragOutside, Point scale, SDL_RendererFlip flip) :
	Control(ControlType::BUTTON, rectangle, anchored, dragOutside, scale, flip)
{
	this->check = check;
}

Checkbox::~Checkbox()
{
}

bool Checkbox::Check() const
{
	return check;
}

void Checkbox::Check(bool check)
{
	this->check = check;
}

bool Checkbox::Update()
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
		check = !check;
		if (on) state = ControlState::FOCUSED;
		else state = ControlState::NORMAL;
		onRelease.Invoke(check);
		break;
	}

	return true;
}

bool Checkbox::Draw() const
{
	Texture* texture = nullptr;
	switch (state)
	{
	case ControlState::DISABLED: texture = check ? texCheckDisabled : texUncheckDisabled; break;
	case ControlState::NORMAL:   texture = check ? texCheckNormal   : texUncheckNormal;   break;
	case ControlState::FOCUSED:  texture = check ? texCheckFocused  : texUncheckFocused;  break;
	case ControlState::PRESSED:  texture = check ? texCheckPressed  : texUncheckPressed;  break;
	case ControlState::SELECTED: texture = check ? texCheckSelected : texUncheckSelected; break;
	}

	render->DrawTexture(texture, rectangle.Position(), scale, anchored, nullptr, 0, flip);

	if (!config->Get(0)) return true;

	Uint8 plus = 0;
	if (!check) plus = 150;
	switch (state)
	{
	case ControlState::DISABLED: render->DrawRectangle(rectangle, { 100, 100, 100, 80 }, {}, { 1, 1 }, anchored); break;
	case ControlState::NORMAL:   render->DrawRectangle(rectangle, {plus, 255,plus, 80 }, {}, { 1, 1 }, anchored); break;
	case ControlState::FOCUSED:  render->DrawRectangle(rectangle, { 255, 255,plus, 80 }, {}, { 1, 1 }, anchored); break;
	case ControlState::PRESSED:  render->DrawRectangle(rectangle, {plus, 255, 255, 80 }, {}, { 1, 1 }, anchored); break;
	case ControlState::SELECTED: render->DrawRectangle(rectangle, {Uint8(100 + plus), Uint8(100 + plus), 255, 80 }, {}, { 1, 1 }, anchored); break;
	}

	return true;
}

bool Checkbox::Manipulate()
{
	if (Maths::CheckCollision(Rect{ input->GetMousePosition(), 1.0f, 1.0f }, { rectangle.Position(), rectangle.Size().Multiply(scale) })
		&& input->GetMouseButtonDown(MouseCode::BUTTON_LEFT))
	{
		onClick.Invoke();
		state = ControlState::PRESSED;
		(*selectID).Clear();
		return false;
	}

	if (input->GetKeyDown(submitKey))
	{
		check = !check;
		onSubmit.Invoke(check);
	}

	return true;
}
