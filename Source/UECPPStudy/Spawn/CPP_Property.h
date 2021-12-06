#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Property.generated.h"

UCLASS()
class UECPPSTUDY_API ACPP_Property : public AActor
{
	GENERATED_BODY()
private:
	//아키 타입 : 해당 클래스 형식으로 만든 블루프린트를 의미합니다
	//인스턴스 타입 : 해당 클래스 형식으로 만든 객체를 의미합니다.
	
	//에디터에서의 설정 여부를 결정합니다
	UPROPERTY(EditAnywhere)//(아키타입 인스턴스)어디서든지 접근하고 수정 가능
		int A = 10;

	UPROPERTY(EditInstanceOnly)//level에 배치한 객체의 경우 에디터에서 수정가능
		int B = 10;

	UPROPERTY(EditDefaultsOnly)//BPediter상에서만 수정가능 (level에 배치하면 안됨)
		int C = 10;

	UPROPERTY(VisibleAnywhere)//보이기만 할뿐 수정은 불가능
		int D = 40;

protected:
	//블루프린트에서 읽을수있고  level에 배치하면 사용가능  카테고리는  "Property" 이다
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category = "Property")
		int Variable = 60;

public:	
	ACPP_Property();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
