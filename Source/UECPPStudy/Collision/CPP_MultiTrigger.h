#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_MultiTrigger.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FMultiLightBeginOverlap, int32, FLinearColor);

UCLASS()
class UECPPSTUDY_API ACPP_MultiTrigger : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

public:	
	ACPP_MultiTrigger();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, //�浹ó���� ������Ʈ
			AActor* OtherActor,											//�ٸ� ��ü
			UPrimitiveComponent* OtherComp,								//�ٸ� ��ü ������Ʈ
			int32 OtherBodyIndex,										//������Ʈ ID
			bool bFromSweep,
			const FHitResult& SweepResult);
public:
	FMultiLightBeginOverlap OnMultiLightBeginOverlap;
};
