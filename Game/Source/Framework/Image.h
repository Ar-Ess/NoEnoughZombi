#pragma once

#include "Control.h"

class Image : public Control
{

	friend class ControlCreation;

public:
	
	virtual ~Image();

private:
	
	Image(Rect rectangle, Texture* texture, Point scale, bool anchored, SDL_RendererFlip flip);
	
	bool Draw() const override;

private:

	Texture* texture = nullptr;

};
