#include "Image.h"

Image::Image(Rect rectangle, Texture* texture, Point scale, bool anchored, SDL_RendererFlip flip) :
	Control(ControlType::IMAGE, rectangle, anchored, false, scale, flip)
{
	this->rectangle.Size(texture->Size());
	this->texture = texture;
}

Image::~Image()
{
}

bool Image::Draw() const
{
    render->DrawTexture(texture, rectangle.Position(), scale, anchored, nullptr, 0, flip);

    if (!config->Get(0)) return true;

    render->DrawRectangle(rectangle, { 0, 255, 0, 80 }, {}, scale, anchored);

    return false;
}
