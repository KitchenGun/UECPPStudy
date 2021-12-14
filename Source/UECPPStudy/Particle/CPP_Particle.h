#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Particle.generated.h"

UCLASS()
class UECPPSTUDY_API ACPP_Particle : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* Particle;

public:	
	ACPP_Particle();

protected:
	virtual void BeginPlay() override;

};
