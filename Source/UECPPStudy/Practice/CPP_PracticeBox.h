#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_PracticeBox.generated.h"

UCLASS()
class UECPPSTUDY_API ACPP_PracticeBox : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY()
		class UMaterialInstanceDynamic* Material[2];
protected:
	UPROPERTY(EditAnyWhere)//��ŰŸ�Կ��� �����ֱ⸸ �Ѵ�
		class UStaticMeshComponent* Mesh[2];//���漱��
public:	
	ACPP_PracticeBox();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void ChangeColor(int32 index,FLinearColor color);
};
