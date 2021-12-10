#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_ComponentBeginOverlap.generated.h"

UCLASS()
class UECPPSTUDY_API ACPP_ComponentBeginOverlap : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;
	UPROPERTY(VisibleDefaultsOnly)
		class UPointLightComponent* PointLight;
public:	
	ACPP_ComponentBeginOverlap();

protected:
	virtual void BeginPlay() override;

	
	
private:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, //충돌처리할 컴포넌트
			AActor* OtherActor,											//다른 객체
			UPrimitiveComponent* OtherComp,								//다른 객체 컴포넌트
			int32 OtherBodyIndex,										//오브젝트 ID
			bool bFromSweep,									
			const FHitResult& SweepResult);
	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, 
			AActor* OtherActor, 
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);
};
