#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_LineTrace.generated.h"
//�̺�Ʈ �븮��(����� �ٸ�����) : Ŭ���� ���ο� �����ؼ� �ش� Ŭ���������� ����� �����Ѱ��� �̺�Ʈ ��������Ʈ��� ��
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLineTraceResult, class AActor*, InActor, FLinearColor, InColor);

UCLASS()
class UECPPSTUDY_API ACPP_LineTrace : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;
public:	
	ACPP_LineTrace();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
private:
	UFUNCTION()
		void StartJump(class AActor* InActor, FLinearColor InColor);
private:
	UPROPERTY(BlueprintAssignable)//�������Ʈ���� ����ϱ� ���ؼ� ��� ��Ƽ�ɽ�Ʈ �븮�ڸ� ��밡��
	FLineTraceResult OnLineTraceResult;
private:
	TArray<class ACPP_Cylinder*> Cylinders;
};
