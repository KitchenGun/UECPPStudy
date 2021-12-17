#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_LineTrace.generated.h"
//이벤트 대리자(현재와 다른거임) : 클래스 내부에 선언해서 해당 클래스에서만 사용이 가능한것을 이벤트 델리게이트라고 함
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
	UPROPERTY(BlueprintAssignable)//블루프린트에서 사용하기 위해서 사용 멀티케스트 대리자만 사용가능
	FLineTraceResult OnLineTraceResult;
private:
	TArray<class ACPP_Cylinder*> Cylinders;
};
