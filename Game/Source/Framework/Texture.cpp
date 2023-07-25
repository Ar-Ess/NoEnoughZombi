#include "Texture.h"

#include "physfsrwops.h"
#include "Defs.h"
#include "Render.h"

Texture::Texture(const char* path, SDL_Renderer* renderer, bool release)
	: Asset(AssetType::AST_TEXTURE, path)
{
	this->path = path;
	Generate(renderer, release);
}

Texture::Texture(SDL_Surface* surface, SDL_Renderer* renderer)
	: Asset(AssetType::AST_TEXTURE, nullptr)
{
	this->texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

Texture::~Texture()
{
	SDL_DestroyTexture(texture);
}

Point Texture::Size() const
{
	return size;
}

void Texture::Generate(SDL_Renderer* renderer, bool release)
{
	SDL_Surface* surface = nullptr;
	SDL_RWops* rW = nullptr;

	if (release)
	{
		if (PHYSFS_exists(path) == 0)
		{
			LOG("ERROR - FILE %s DOESNT EXIST IN THE SEARCH PATH: %s\n", path, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
			return;
		}

		rW = PHYSFSRWOPS_openRead(path);

		if (!rW)
		{
			LOG("ERROR OPENING FILE %s FOR READING: %s\n", path, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
			return;
		}

		surface = IMG_Load_RW(rW, 0);
	}
	else surface = IMG_Load(path);

	if (!surface)
	{
		LOG("Could not load surface with path: %s. IMG_Load: %s", path, IMG_GetError());
		if (rW) SDL_RWclose(rW);
		return;
	}

	texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (!texture) LOG("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());

	size.Set((float)surface->w, (float)surface->h);

	SDL_FreeSurface(surface);
	if (rW) SDL_RWclose(rW);
}