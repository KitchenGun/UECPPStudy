#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Trigger.generated.h"

//�븮�� ���� (����� �Ű����� �ʿ��� ��� �Ķ���͸� �䱸�ϴ��� �ۼ������� ����)
DECLARE_DELEGATE(FBoxLightOverlap);
DECLARE_DELEGATE_RetVal_OneParam(FString, FBoxLightColorOverlap, FLinearColor);

UCLASS()
class UECPPSTUDY_API ACPP_Trigger : public AActor
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
	ACPP_Trigger();

protected:
	virtual void BeginPlay() override;

private:	
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, //�浹ó���� ������Ʈ
			AActor* OtherActor,											//�ٸ� ��ü
			UPrimitiveComponent* OtherComp,								//�ٸ� ��ü ������Ʈ
			int32 OtherBodyIndex,										//������Ʈ ID
			bool bFromSweep,
			const FHitResult& SweepResult);
	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

public:
	FBoxLightOverlap OnBoxLightBeginOverlap;
	FBoxLightOverlap OnBoxLightEndOverlap;
	FBoxLightColorOverlap OnBoxLightColorOverlap;
};

