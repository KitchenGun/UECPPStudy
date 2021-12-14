#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_PracticeBox.generated.h"

UCLASS()
class UECPPSTUDY_API ACPP_PracticeBox : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Meshes[3];

public:	
	ACPP_PracticeBox();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnPhysics(int32 index, FLinearColor InColor);
private:
	class UMaterialInstanceDynamic* Materials[3];
	FVector WorldLocations[3];
};
