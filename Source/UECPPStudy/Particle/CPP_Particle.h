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

		//������ ������ ���(uint8�� ��ȯ�Ͽ�)���� ������ ���� ����Ʈ�� �����ϴ� ���ø�
		// bp������ uint8������ �ƴϸ� �����̵�������
		//c++�� Ŭ���� ����ؼ� ������ ����� unreal���� ����ϴ� enum�� ����̴�.
public:	
	ACPP_Particle();

protected:
	virtual void BeginPlay() override;
public:
	UFUNCTION()
	void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

};
