#include "Mixer.h"
#include "Maths.h"

Mixer::Mixer(SoLoud::Soloud* engine)
{
	//mixer = new SoLoud::Bus();
	this->engine = engine;
	//echo->setParams(0.06f, 0.95);
	//reverb->createInstance()->setFilterParameter(SoLoud::FreeverbFilter::FILTERPARAM::WET, 0.5f);
	//reverb->setParams(0.5, 500.f, 500.f, 1);
}

Mixer::~Mixer()
{

}

void Mixer::SetChild(Mixer* child)
{
	child->parent = this;
}

void Mixer::Volume(float volume)
{
	volume = Maths::Clamp(volume, 0, 1);
	this->volume = volume;
}

float Mixer::Volume()
{
	return volume;
}

void Mixer::Pan(float pan)
{
	pan = Maths::Clamp(pan, -1, 1);
	this->pan = pan;
}

float Mixer::Pan()
{
	return pan;
}

void Mixer::Play(SoLoud::Wav* audio, float delay)
{
	Params params = RealParams(this, { volume, pan, echo });
	//audio->setFilter(1, reverb);
	if (delay <= 0) engine->play(*audio, params.volume, params.pan);
	else engine->playClocked(delay, *audio, params.volume, params.pan);
}

Mixer::Params Mixer::RealParams(Mixer* source, Params params)
{
	if (!source->parent) return params;

	// Volume logic
	params.volume *= source->parent->volume;

	// Pan logic
	params.pan += source->parent->pan;

	// Reverb logic
	//if (!params.echo) params.echo = parent->echo;
	//else if (parent->echo)
	//{
	//}

	params.pan = Maths::Clamp(params.pan, -1, 1);
	return RealParams(source->parent, params);
}
