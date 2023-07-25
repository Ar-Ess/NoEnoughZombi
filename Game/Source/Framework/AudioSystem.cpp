#include "AudioSystem.h"

AudioSystem::AudioSystem() :
	Module()
{

}

AudioSystem::~AudioSystem()
{
}

bool AudioSystem::Awake()
{
	engine = new SoLoud::Soloud();

	Mixer* master   = new Mixer(engine);
		Mixer* music    = new Mixer(engine);
		Mixer* sfx      = new Mixer(engine);
			Mixer* ambience = new Mixer(engine);
		Mixer* voices   = new Mixer(engine);

	master->SetChild(sfx);
		sfx->SetChild(ambience);
	master->SetChild(music);
	master->SetChild(voices);

	mixers.Add(master  , Mix::MIX_MASTER);
	mixers.Add(music   , Mix::MIX_MUSIC);
	mixers.Add(sfx     , Mix::MIX_SFX);
	mixers.Add(ambience, Mix::MIX_SFX_AMBIENCE);
	mixers.Add(voices  , Mix::MIX_VOICES);

	return true;
}

bool AudioSystem::Start()
{
	LOG("Loading Audio System");
	bool ret = true;

	engine->init();

	return ret;
}

bool AudioSystem::CleanUp()
{
	LOG("Freeing Audio System");

	engine->deinit();
	delete engine;

	mixers.Clear();

	return true;
}

void AudioSystem::Play(Audio* audio, Mix mixer, float delay)
{
	this->mixers.Get(mixer)->Play(audio->audio, delay);
}

void AudioSystem::SetMixerVolume(float volume, Mix mixer)
{
	mixers.Get(mixer)->Volume(volume);
}

float AudioSystem::GetMixerVolume(Mix mixer)
{
	return mixers.Get(mixer)->Volume();
}

void AudioSystem::SetMixerPan(float pan, Mix mixer)
{
	mixers.Get(mixer)->Pan(pan);
}

float AudioSystem::GetMixerPan(Mix mixer)
{
	return mixers.Get(mixer)->Pan();
}