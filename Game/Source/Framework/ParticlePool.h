#ifndef __PARTICLE_POOL_H__
#define __PARTICLE_POOL_H__

#include "Particle.h"
#include "Emitter.h"
#include "Point.h"
#include <vector>
#include "Render.h"

enum class ParticleState
{
	PARTICLE_STATE_NOT_DEF,
	PARTICLE_ALIVE_DRAWN,
	PARTICLE_ALIVE_NOT_DRAWN,
	PARTICLE_DEAD
};

class ParticlePool
{
private:

	int poolSize = 0;
	Particle* firstAvailable;
	std::vector<Particle*> particleArray;

public:

	ParticlePool(Emitter* emitter, Render* render);
	virtual ~ParticlePool();

	// Generates a new particle each time it's called
	void Generate(Point pos, float startSpeed, float endSpeed, float angle, float rotSpeed, float startSize, float endSize, unsigned int life, Rect textureRect, SDL_Color startColor, SDL_Color endColor, SDL_BlendMode blendMode, bool vortexSensitive);

	// Update (move and draw) particles in the pool.
	// IMPORTANT NOTE: This method returns:
	//		- PARTICLE_ALIVE_DRAWN: if the particle is still alive and has been drawn succesfully
	//      - PARTICLE_ALIVE_NOT_DRAWN:  if the particle is alive and has NOT been drawn succesfully
	//		- PARTICLE_DEAD: if is particle is no longer alive

	ParticleState Update();
};

#endif
