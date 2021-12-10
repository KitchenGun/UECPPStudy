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
};
