#pragma once

#include "Module.h"
#include "Map.h"

class Render;
class Font;
class Texture;
class Audio;
class Asset;

class AssetsManager : public Module
{
public:

	// Mount is the name of the compressed file if running in release mode
	AssetsManager(bool release, const char* mount, Render* render);

	virtual ~AssetsManager();

	bool Start();

	bool Cleanup();

	void NewAudio(const char* path, const char* identifier, float volume = 1, float pan = 0);

	void NewFont(const char* path, const char* identifier);

	void NewTexture(const char* path, const char* identifier);

	Audio* GetAudio(const char* identifier);

	Font* GetFont(const char* identifier);
	
	Texture* GetTexture(const char* identifier);

	//size_t LoadXML(const char* path, char** buffer);

private:

	Render* render = nullptr;
	Map<const char*, Asset*> assets;
	bool release = false;
	const char* mount = nullptr;

};
