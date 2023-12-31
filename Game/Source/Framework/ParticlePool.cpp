#include "ParticlePool.h"
#include "Emitter.h"
#include <assert.h>

//#include "Brofiler\Brofiler.h"

// This pool constructor sets our particles to available
ParticlePool::ParticlePool(Emitter* emitter, Render* render)
{
	// Fill the pool according to poolSize needed for the emitter
	poolSize = emitter->GetPoolSize();
	for (unsigned int i = 0; i < poolSize; ++i) particleArray.push_back(new Particle(render, emitter->particles));
	// new Particle(render, emitter->particles)[poolSize]

	// The first particle is available
	firstAvailable = particleArray[0];

	// Each particle points to the next one
	for (int i = 0; i < poolSize - 1; i++)
		particleArray[i]->SetNext(particleArray[i + 1]);

	// The last particle points to nullptr indicating the end of the vector
	particleArray[poolSize - 1]->SetNext(nullptr);
}

ParticlePool::~ParticlePool()
{
	for (unsigned int i = 0; i < poolSize; ++i)
	{
		delete particleArray[i];
		particleArray[i] = nullptr;
	}
	particleArray.clear();
	firstAvailable = nullptr;
}

void ParticlePool::Generate(Point pos, float startSpeed, float endSpeed, float angle, float rotSpeed, float startSize, float endSize, unsigned int life, Rect textureRect, SDL_Color startColor, SDL_Color endColor, SDL_BlendMode blendMode, bool vortexSensitive)
{
	// Check if the pool is not full
	assert(firstAvailable != nullptr);

	// Remove it from the available list
	Particle* newParticle = firstAvailable;
	firstAvailable = newParticle->GetNext();

	// Initialize new alive particle
	newParticle->Init(pos, startSpeed, endSpeed, angle, rotSpeed, startSize, endSize, life, textureRect, startColor, endColor, blendMode, vortexSensitive);
}

ParticleState ParticlePool::Update()
{
	ParticleState retState = ParticleState::PARTICLE_STATE_NOT_DEF;

	//BROFILER_CATEGORY("Pool update", Profiler::Color::LightCyan)
	for (int i = 0; i < poolSize; i++)
	{
		if (particleArray[i]->IsAlive())
		{
			particleArray[i]->Update();

			if (particleArray[i]->Draw())
				retState = ParticleState::PARTICLE_ALIVE_DRAWN;
			else
				retState = ParticleState::PARTICLE_ALIVE_NOT_DRAWN;
		}
		else // if a particle dies it becomes the first available in the pool
		{
			// Add this particle to the front of the vector
			particleArray[i]->SetNext(firstAvailable);
			firstAvailable = particleArray[i];
			retState = ParticleState::PARTICLE_DEAD;
		}
	}

	return retState;
}