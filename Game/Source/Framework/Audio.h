#pragma once

#include "Asset.h"
#include "External/Soloud/include/soloud_wav.h"

class Audio : public Asset
{

	friend class AudioSystem;
	friend class AssetsManager;

public:

	~Audio() override;

private:

	Audio(const char* path, bool release, float volume, float pan);

	bool LoadAudio(bool release);

private:

	SoLoud::Wav* audio = nullptr;
	float volume = 1;
	float pan = 0;

};
