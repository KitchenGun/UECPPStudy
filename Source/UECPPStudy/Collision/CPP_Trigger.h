#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Trigger.generated.h"

//대리자 형식 (현재는 매개변수 필요없어서 몇개의 파라미터를 요구하는지 작성되있지 않음)
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

public:
	FBoxLightOverlap OnBoxLightBeginOverlap;
	FBoxLightOverlap OnBoxLightEndOverlap;
	FBoxLightColorOverlap OnBoxLightColorOverlap;
};

