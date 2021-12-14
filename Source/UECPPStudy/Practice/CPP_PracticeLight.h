#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_PracticeLight.generated.h"

UCLASS()
class UECPPSTUDY_API ACPP_PracticeLight : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;
	UPROPERTY(VisibleDefaultsOnly)
		class USpotLightComponent* SpotLights[3];
public:	
	ACPP_PracticeLight();

protected:
	virtual void BeginPlay() override;
private:
	UFUNCTION()
		void OnLight (int index,FLinearColor color);

};
