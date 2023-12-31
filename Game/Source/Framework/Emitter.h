#ifndef __EMITTER_H__
#define __EMITTER_H__

#include "Point.h"
#include "PerfTimer.h"
#include "ParticleSystem.h"
#include "SDL/include/SDL.h"
#include "Render.h"

struct SDL_Texture;
struct EmitterData;
class ParticleSystem;

class Emitter
{
private:
	friend class ParticlePool;

	ParticleSystem* particles = nullptr;

	// Particles size and movement
	Point pos = { 0.0f, 0.0f };
	Point angleRange = { 0.0f, 360.0f };
	float startSpeed = 0.0f;
	float endSpeed = 0.0f;
	float startSize = 0.0f;
	float endSize = 0.0f;
	double rotSpeed = 0;

	// Particles emission
	int emissionRate = 0;
	unsigned int emitNumber = 0u;
	unsigned int emitVariance = 0u;
	unsigned int maxParticleLife = 0u;
	unsigned int maxParticlesPerFrame = 0u;

	// Pool
	ParticlePool* emitterPool = nullptr;
	int poolSize = 0;

	// Emission time
	PerfTimer stopTimer;
	PerfTimer emissionTimer;
	PerfTimer lifeTimer;
	double stopTime = 0.0f;
	double emissionTime = 0.0f;
	double lifetime = -1.0f;
	bool active = false;

	// Color and render properties
	SDL_Color startColor = { 0, 0, 0, 0 };
	SDL_Color endColor = { 0, 0, 0, 0 };
	Rect textureRect;
	SDL_BlendMode blendMode = SDL_BlendMode::SDL_BLENDMODE_NONE;
	float timeStep = 0.0f;

	// Random control parameters
	Point rotSpeedRand = { 0.0f, 0.0f };
	Point startSpeedRand = { 0.0f, 0.0f };
	Point endSpeedRand = { 0.0f, 0.0f };
	Point emitVarianceRand = { 0.0f, 0.0f };
	Point lifeRand = { 0.0f, 0.0f };
	Point startSizeRand = { 0.0f, 0.0f };
	Point endSizeRand = { 0.0f, 0.0f };

	// Vortex control parameters
	bool vortexSensitive = false;

public:

	Emitter(Point pos, EmitterData data, ParticleSystem* particles);
	// fPoint pos, uint emitNumber, uint emitVariance, uint maxParticleLife, fPoint angleRange, double rotSpeed, float maxSpeed, float startSize, float endSize, SDL_Rect textureRect, SDL_Color startColor = { 0, 0, 0, 0 }, SDL_Color endColor = { 0, 0, 0, 0 }, SDL_BlendMode blendMode = SDL_BlendMode::SDL_BLENDMODE_NONE, double lifetime = -1.0f
	virtual ~Emitter();

	void Update(float dt);
	bool Draw();

	// Generates random number between given range
	float RangeRandomNum(float min = -1.0f, float max = 1.0f);

	// Returns emitter pool size
	int GetPoolSize() const;

	// Starts emission specified by timer, if not emission time is infinite
	void StartEmission(double timer = -1.0f);

	// Stops emission specified by timer, if not emission stop time is infinite
	void StopEmission(double timer = 0.0f);

	// Emitter move methods
	void MoveEmitter(Point newPos);
	Point GetEmitterPos() const;

	void VortexSensitive(bool sensitive);
};

#endif