#pragma once

#include "Asset.h"
#include "Point.h"
#include "External/SDL_ttf/include/SDL_ttf.h"

class Texture;

class Font : public Asset
{

	friend class AssetsManager;

public:

	~Font() override;

	Texture* GenerateTexture(const char* text, unsigned int size, SDL_Color color, int width, SDL_Color shade, SDL_Renderer* renderer);

	// Calculates the size in pixels of a text.
	// The width parameter stands for the wrapped maximum width befor new line.
	Point CalculateSize(const char* text, float width = 0);

	unsigned int Size() const
	{
		return size;
	}

private:

	Font(const char* path, bool release);

	bool CreateFont(unsigned int size);

private:

	TTF_Font* font = nullptr;
	unsigned int size = 14;
	bool release = false;

};
