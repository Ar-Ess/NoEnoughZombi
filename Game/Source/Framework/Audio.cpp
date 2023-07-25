#include "Audio.h"
#include <string>
#include "PhysFS/include/physfsrwops.h"
#include "Defs.h"
#include "SoLoud/include/soloud_file.h"

Audio::Audio(const char* path, bool release, float volume, float pan) :
	Asset(AssetType::AST_AUDIO, path)
{
	this->path = path;
	this->audio = new SoLoud::Wav();
	this->volume = volume;
	this->pan = pan;
	LoadAudio(release);
}

Audio::~Audio()
{
}

bool Audio::LoadAudio(bool release)
{
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

		// Getting data from the rW

		// Using some function inside "SoLoud::Wav" class to load data

		return true;
	}

	audio->load(path);
}
