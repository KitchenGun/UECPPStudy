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
		class UPointLightComponent* PointLight[2];
public:	
	ACPP_PracticeLight();

protected:
	virtual void BeginPlay() override;
protected:
	UFUNCTION()
		void ChangeColor(int index,FLinearColor color);

};
