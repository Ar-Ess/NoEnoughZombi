#pragma once

#include "Control.h"
#include "Texture.h"
#include "Font.h"
#include "Alignment.h"

class Text : public Control
{

	friend class ControlCreation;

public:

	virtual ~Text();

	unsigned int Size() const;

	void Set(const char* text = nullptr, Font* font = nullptr, int size = -1);

	void Align(Alignment align);

	Alignment Align() const;

private:

	Text(Rect rectangle, const char* text, Alignment align, Point scale, bool anchored, SDL_RendererFlip flip);

	bool Draw() const override;

	void OnTextDisable();

	void OnTextEnable();

	void CalculateBoundsPosition();

public:

	SDL_Color normalColor = { 255, 255, 255, 255 };
	SDL_Color disabledColor = { 100, 100, 100, 255 };
	SDL_Color shadeColor = { 0, 0, 0, 0 };
	bool shade = false;

private:

	Alignment align = Alignment::TOP_LEFT;
	Rect bounds = {};
	const char* text = nullptr;
	Texture* texture = nullptr;
	Font* font = nullptr;
	SDL_Color* color = nullptr;

};
