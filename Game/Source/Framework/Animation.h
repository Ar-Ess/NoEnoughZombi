#pragma once

#include "Array.h"
#include "Flag.h"
#include "Texture.h"
#include "MathUtils.h"

class Animation
{
private:

	Texture* tex = nullptr;

public:

	// frameSize: Width and height of each frame. They must be consistens
	// maxFrameHorizontal: How many frames there are in each horizontal row of the texture. Set 0 if it is just one row.
	// frameOffset: offset for each frame. In case there are spacings inbetween frames.
	Animation(Texture* tex, unsigned int frames, Point frameSize, unsigned int maxFrameHorizontal = 0, Point frameOffset = { 0, 0 })
	{
		this->tex = tex;
		this->size = frames;
		this->frameSize = frameSize;
		this->frameOffset = frameOffset;
	}

	unsigned int Size() const
	{
		return size;
	}

	Texture* Texture() const
	{
		return tex;
	}

	Rect CurrentFrame(float dt)
	{
		time += dt;

	}

	float FPS() const
	{
		return fps;
	}
	void FPS(float fps)
	{
		this->fps = fps;
	}

	// set times to 0 for infinite loop
	void PingPong(bool active)
	{
		config.Set(ANIM_PING_PONG, active);
	}

	// set times to 0 for infinite loop
	void Loop(bool active, unsigned int times = 0)
	{
		if (times == 1) return config.Set(ANIM_LOOP, false);
		this->loops = times;
		config.Set(ANIM_LOOP, active);
	}

	bool IsFinished() const
	{
		unsigned int index = CurrentFrameIndex();
		return !config.Get(ANIM_LOOP) && (config.Get(ANIM_PING_PONG) ? index == 0 : index == size - 1);
	}

	void Reset()
	{
		time = 0.0f;
		loopsDone = 0;
	}

private:

	unsigned int CurrentFrameIndex() const
	{
		int index = Maths::Floor(time / fps);
		Maths::Clamp(index, 0, size - 1);
		return index;
	}

private:

	enum AnimConfig
	{
		ANIM_LOOP,
		ANIM_PING_PONG,
	};

	Point frameSize = { 0, 0 };
	Point frameOffset = { 0, 0 };
	unsigned int maxFrameHorizontal = 0;
	float fps = 1;
	Flag config;
	unsigned int loops = 0;
	unsigned int loopsDone = 0;

	unsigned int size = 0;
	float time = 0;

};
