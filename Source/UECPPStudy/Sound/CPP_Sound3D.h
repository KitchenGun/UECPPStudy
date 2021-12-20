#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Sound3D.generated.h"

UCLASS()
class UECPPSTUDY_API ACPP_Sound3D : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere)
		class USoundCue* Sound;
	UPROPERTY(EditAnywhere)
		class USoundAttenuation* SoundAttenuation;
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;
public:	
	ACPP_Sound3D();

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
		void Repeat();

	UFUNCTION()
		void Stop();
private:
	class UAudioComponent* Audio;

};
