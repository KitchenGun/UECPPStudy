#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_ParticleTrigger.generated.h"

UCLASS()
class UECPPSTUDY_API ACPP_ParticleTrigger : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;
public:	
	ACPP_ParticleTrigger();

protected:
	virtual void BeginPlay() override;

};
