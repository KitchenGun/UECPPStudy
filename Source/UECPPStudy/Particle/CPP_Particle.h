#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CPP_Particle.generated.h"

UCLASS()
class UECPPSTUDY_API ACPP_Particle : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* Particle;
	UPROPERTY(EditAnywhere)
		TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType;

		//형식이 안전한 방식(uint8로 변환하여)으로 열거형 값을 바이트로 저장하는 템플릿
		// bp에서는 uint8형식이 아니면 노출이되지않음
		//c++은 클래스 사용해서 열거형 사용함 unreal에서 사용하는 enum문 방식이다.
public:	
	ACPP_Particle();

protected:
	virtual void BeginPlay() override;
public:
	UFUNCTION()
	void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

};
