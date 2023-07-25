#include "Text.h"
#include <functional>

Text::Text(Rect rectangle, const char* text, Alignment align, Point scale, bool anchored, SDL_RendererFlip flip) :
	Control(ControlType::TEXT, rectangle, anchored, false, scale, flip)
{
	this->rectangle = rectangle;
	this->text = text;
	this->align = align;
	this->bounds.Size(0, 0);
	CalculateBoundsPosition();

	this->color = &normalColor;

	this->onDisable += std::bind(&Text::OnTextDisable, this);
	this->onEnable += std::bind(&Text::OnTextEnable, this);
}

Text::~Text()
{
	delete texture;
	texture = nullptr;
	font = nullptr;
	text = nullptr;
	this->onDisable -= std::bind(&Text::OnTextDisable, this);
	this->onEnable -= std::bind(&Text::OnTextEnable, this);
}

bool Text::Draw() const
{
	render->DrawTexture(texture, bounds.Position(), scale, anchored, nullptr, 0, flip);

	if (!config->Get(0)) return true;

	render->DrawRectangle(rectangle, {   0, 255,   0, 80 }, {}, {1, 1}, anchored);
	render->DrawRectangle(bounds, { 175, 255, 175, 80 }, {}, { 1, 1 }, anchored);

	return true;
}

void Text::OnTextDisable()
{
	color = &disabledColor;
	Set(text, font, Size());
}

void Text::OnTextEnable()
{
	color = &normalColor;
	Set(text, font, Size());
}

void Text::CalculateBoundsPosition()
{
	bounds.Position(Rect(rectangle.Position(), rectangle.Size() - bounds.Size()).Position(align));
}

void Text::Set(const char* text, Font* font, int size)
{
	font = font ? font : this->font;
	if (!font) return;

	text = text ? text : this->text;
	size = size > -1 ? size : Size();

	SDL_Color shadeC = shadeColor;
	if (!shade) shadeC.a = 0;

	delete texture;
	texture = font->GenerateTexture(text, size, *color, (int)rectangle.w, shadeC, render->Renderer());
	bounds.Size(font->CalculateSize(text, rectangle.w));
	CalculateBoundsPosition();


	this->font = font;
	this->text = text;
}

void Text::Align(Alignment align)
{
	this->align = align;
	CalculateBoundsPosition();
}

Alignment Text::Align() const
{
	return align;
}

unsigned int Text::Size() const
{
	if (!font) return 0;

	return font->Size();
}
