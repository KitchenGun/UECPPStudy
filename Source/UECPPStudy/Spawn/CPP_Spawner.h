#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Spawner.generated.h"

UCLASS()
class UECPPSTUDY_API ACPP_Spawner : public AActor
{
	GENERATED_BODY()
private:
	//Uclass 유형의 안전성을 보장해주는 템플릿 클래스
	//템플릿 형태의 파생클래스를 할당받을 수 있습니다.
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AActor> SpawnClasses[3];

private:
	class ACPP_Mesh* Meshes[3];

public:	
	ACPP_Spawner();

protected:
	virtual void BeginPlay() override;

};
