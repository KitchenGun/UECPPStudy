#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Sound2D.generated.h"

UCLASS()
class UECPPSTUDY_API ACPP_Sound2D : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere)
		class USoundCue* Sound;
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;


public:	
	ACPP_Sound2D();

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
private:
	class UAudioComponent* Audio;
};
