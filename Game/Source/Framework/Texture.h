#pragma once

#include "Asset.h"
#include "Point.h"
#include "External/SDL_image/include/SDL_image.h"

struct SDL_Surface;

class Texture : public Asset
{

	friend class Render;
	friend class AssetsManager;
	friend class Font;

public:

	~Texture() override;

	Point Size() const;

private:

	Texture(const char* path, SDL_Renderer* render, bool release);

	Texture(SDL_Surface* surface, SDL_Renderer* renderer);

	void Generate(SDL_Renderer* renderer, bool release);

private:

	SDL_Texture* texture = nullptr;
	Point size = {};

};