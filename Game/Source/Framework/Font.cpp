#include "Font.h"
#include "Maths.h"
#include "PhysFS/include/physfsrwops.h"
#include "Defs.h"
#include "Texture.h"

Font::Font(const char* path, bool release) :
	Asset(AssetType::AST_FONT, path)
{
	this->release = release;
}

Font::~Font()
{
}

Texture* Font::GenerateTexture(const char* text, unsigned int size, SDL_Color color, int width, SDL_Color shade, SDL_Renderer* renderer)
{
	if (!font || size != this->size) 
		if (!CreateFont(size)) 
			return nullptr;

	SDL_Surface* surface = shade.a != 0 ?
		TTF_RenderText_Shaded_Wrapped(font, text, color, shade, width) :
		TTF_RenderText_Blended_Wrapped(font, text, color, width);

	if (!surface) return nullptr;

	return new Texture(surface, renderer);
}

Point Font::CalculateSize(const char* text, float width)
{
	int w, h;
	if (TTF_SizeText(font, text, &w, &h) != 0) return {0, 0};
	Point size = { float(w), float(h) };

	if (width == 0) return size;

	int ratio = (int)Maths::Ceil(size.x / width);

	if (ratio > 1) size.x = width;
	size.y *= ratio;

	return size;
}

bool Font::CreateFont(unsigned int size)
{
	if (font) TTF_CloseFont(font);

	if (release)
	{
		if (PHYSFS_exists(path) == 0)
		{
			LOG("ERROR - FILE %s DOESNT EXIST IN THE SEARCH PATH: %s\n", path, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
			return false;
		}

		SDL_RWops* rW = PHYSFSRWOPS_openRead(path);

		if (!rW)
		{
			LOG("ERROR OPENING FILE %s FOR READING: %s\n", path, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
			return false;
		}

		font = TTF_OpenFontRW(rW, 0, size);
	}
	else font = TTF_OpenFont(path, size);

	if (!font) return false;

	this->size = size;

	return true;
}
