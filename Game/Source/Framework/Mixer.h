#pragma once

#include "Array.h"
#include "External/Soloud/include/soloud_bus.h"
#include "External/Soloud/include/soloud_wav.h"
#include "External/Soloud/include/soloud.h"
#include "External/Soloud/include/soloud_echofilter.h"
#include "External/Soloud/include/soloud_freeverbfilter.h"

class Mixer
{

	friend class AudioSystem;

	struct Params
	{
		float volume = 1;
		float pan = 0;
		SoLoud::EchoFilter* echo = nullptr;
	};

private:

	Mixer(SoLoud::Soloud* engine);

	~Mixer();

	void SetChild(Mixer* child);

	void Volume(float volume);
	float Volume();

	void Pan(float pan);
	float Pan();

	void Play(SoLoud::Wav* audio, float delay);

	Params RealParams(Mixer* source, Params params);

private:

	Mixer* parent = nullptr;
	SoLoud::Soloud* engine = nullptr;
	SoLoud::EchoFilter* echo = new SoLoud::EchoFilter();
	SoLoud::FreeverbFilter* reverb = new SoLoud::FreeverbFilter();
	
	float volume = 1;
	float pan = 0;

};
