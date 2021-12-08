#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Spawner.generated.h"

UCLASS()
class UECPPSTUDY_API ACPP_Spawner : public AActor
{
	GENERATED_BODY()
private:
	//Uclass ������ �������� �������ִ� ���ø� Ŭ����
	//���ø� ������ �Ļ�Ŭ������ �Ҵ���� �� �ֽ��ϴ�.
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AActor> SpawnClasses[3];

private:
	class ACPP_Mesh* Meshes[3];

public:	
	ACPP_Spawner();

protected:
	virtual void BeginPlay() override;

};
