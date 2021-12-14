#include "Particle/CPP_Particle.h"
#include "../Utilities/CHelpers.h"
#include "Particles/ParticleSystemComponent.h"

ACPP_Particle::ACPP_Particle()
{
	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Particle, "Particle");
	UParticleSystem* particle;
	CHelpers::GetAsset<UParticleSystem>(&particle, "ParticleSystem'/Game/Particles/P_Explosion1.P_Explosion1'");
	Particle->SetTemplate(particle);
	Particle->bAutoActivate = false;
}

void ACPP_Particle::BeginPlay()
{
	Super::BeginPlay();

	Particle->SetActive(true);
}


