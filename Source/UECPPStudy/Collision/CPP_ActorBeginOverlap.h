#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_ActorBeginOverlap.generated.h"

UCLASS()
class UECPPSTUDY_API ACPP_ActorBeginOverlap : public AActor
{
	GENERATED_BODY()
	
private:
	//editer�� �������� �� ������Ʈ
	//������� �κ��� ������ ������ ���� ������Ʈ
	UPROPERTY(VisibleDefaultsOnly)//VisibleDefaultsOnly
		class UBoxComponent* Box;
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* TextRender;
	
public:	
	ACPP_ActorBeginOverlap();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnBeginOverlap(AActor* OverlapedActor, AActor* OtherActor);
	UFUNCTION()
		void OnBeginOverlap2(AActor* OverlapedActor, AActor* OtherActor);
	UFUNCTION()
		void OnEndOverlap(AActor* OverlapedActor, AActor* OtherActor);
};
