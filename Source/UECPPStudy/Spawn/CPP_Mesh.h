#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Mesh.generated.h"

UCLASS()
class UECPPSTUDY_API ACPP_Mesh : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY()
	class UMaterialInstanceDynamic* Material;
protected:
	UPROPERTY(EditAnywhere)
		float Time = 1.0f;
	UPROPERTY(VisibleDefaultsOnly)//아키타입에서 보여주기만 한다
		class UStaticMeshComponent* Mesh;//전방선언
public:	
	ACPP_Mesh();

protected:
	virtual void BeginPlay() override;


private:
	UFUNCTION()
		void ChangeColor();
};
