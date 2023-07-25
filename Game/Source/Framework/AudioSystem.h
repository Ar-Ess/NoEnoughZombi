#pragma once

#include "Module.h"
#include "Audio.h"
#include "Mixer.h"
#include "Map.h"

enum class Mix
{
	MIX_MASTER,
	MIX_MUSIC,
	MIX_SFX,
	MIX_SFX_AMBIENCE,
	MIX_VOICES
};

class AudioSystem : public Module
{

	friend class App;

public:
	
	virtual ~AudioSystem();

	void Play(Audio* audio, Mix mixer, float delay = 0);

	void SetMixerVolume(float volume, Mix mixer);
	float GetMixerVolume(Mix mixer);

	void SetMixerPan(float pan, Mix mixer);
	float GetMixerPan(Mix mixer);

private:
	
	AudioSystem();
	
	bool Awake() override;
	
	bool Start() override;
	
	bool CleanUp() override;

private:

	SoLoud::Soloud* engine = nullptr;

	Map<Mixer*, Mix> mixers;

};