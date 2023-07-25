#include "AssetsManager.h"

#include "physfsrwops.h"
#include "physfsrwops.c"
#include "Font.h"
#include "Audio.h"
#include "Texture.h"
#include "Render.h"

AssetsManager::AssetsManager(bool release, const char* mount, Render* render) : Module()
{
	this->render = render;
	this->mount = mount;
	this->release = release;
}

AssetsManager::~AssetsManager()
{
}

bool AssetsManager::Start()
{
	LOG("Loading Assets Manager");
	bool ret = true;

	if (release && PHYSFS_init(nullptr) == 0)
	{
		LOG("ERROR INITIALIZING PHYSFS LIBRARY: %s\n", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
		ret = false;
	}

	if (release && PHYSFS_mount(mount, nullptr, 1) == 0)
	{
		LOG("ERROR ADDING ARCHIVE TO SEARCH PATH: %s\n", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
		ret = false;
	}

	if (TTF_Init() == -1)
	{
		LOG("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		ret = false;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		LOG("Could not initialize PNG Image lib. IMG_Init: %s", IMG_GetError());
		ret = false;
	}

	if (IMG_Init(IMG_INIT_JPG) == 0)
	{
		LOG("Could not initialize JPG Image lib. IMG_Init: %s", IMG_GetError());
		ret = false;
	}

	return ret;
}

//size_t AssetsManager::LoadXML(const char* path, char** buffer)
//{
//	if (PHYSFS_exists(path) == 0)
//		LOG("ERROR - FILE %s DOESNT EXIST IN THE SEARCH PATH: %s\n", path, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
//
//	PHYSFS_file* file = PHYSFS_openRead(path);
//	if (file == NULL)
//		LOG("ERROR OPENING FILE %s FOR READING: %s\n", path, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
//
//	if (!PHYSFS_eof(file))
//	{
//		PHYSFS_sint64 size = PHYSFS_fileLength(file);
//
//		*buffer = new char[size];
//
//		PHYSFS_sint64 numBytesRead = PHYSFS_readBytes(file, *buffer, size);
//		if (numBytesRead == -1)
//			LOG("ERROR READING FROM FILEHANDLE: %s\n", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
//
//		if (numBytesRead == size)
//		{
//			if (PHYSFS_close(file) == 0)
//				LOG("ERROR CLOSING FILEHANDLE: %s\n", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
//
//			return numBytesRead;
//		}
//		else
//		{
//			PHYSFS_close(file);
//			RELEASE_ARRAY(buffer);
//			return 0;
//		}
//	}
//}

bool AssetsManager::Cleanup()
{
	LOG("Assets Manager Cleanup");

	if (release && PHYSFS_deinit() == 0)
		LOG("ERROR DEINITIALIZING THE PHYSFS LIBRARY: %s\n", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));

	TTF_Quit();

	IMG_Quit();

	return true;
}

void AssetsManager::NewAudio(const char* path, const char* identifier, float volume, float pan)
{
	Asset* audio = new Audio(path, release, volume, pan);
	assets.Add(identifier, audio);
}

void AssetsManager::NewFont(const char* path, const char* identifier)
{
	Asset* font = new Font(path, release);
	assets.Add(identifier, font);
}

void AssetsManager::NewTexture(const char* path, const char* identifier)
{
	Asset* font = new Texture(path, render->renderer, release);
	assets.Add(identifier, font);
}

Audio* AssetsManager::GetAudio(const char* identifier)
{
	Asset* asset = assets.Get(identifier);
	if (!asset) return nullptr;
	if (asset->Type() != AssetType::AST_AUDIO) return nullptr;

	return (Audio*)asset;
}

Font* AssetsManager::GetFont(const char* identifier)
{
	Asset* asset = assets.Get(identifier);
	if (!asset) return nullptr;
	if (asset->Type() != AssetType::AST_FONT) return nullptr;

	return (Font*)asset;
}

Texture* AssetsManager::GetTexture(const char* identifier)
{
	Asset* asset = assets.Get(identifier);
	if (!asset) return nullptr;
	if (asset->Type() != AssetType::AST_TEXTURE) return nullptr;

	return (Texture*)asset;
}
