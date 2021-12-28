#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPS/IRifle.h"
#include "CPP_Player.generated.h"//코드->reflection데이터에 추가하고 generated.h를 에디터에서 비추기 위해 사용합니다 

//reflection system
//cpp에 적힌 내용을 editor에서 파악하기 위해서 존재함
//uclass 나 uproperty,ustruct 가 없으면 editor에서 인식이 되지 않음

//construction script  = 생성자
//차이 
//생성자는 객체에 컴포넌트를 추가 시키고 수정이 가능하지만
//construction script는 컴포넌트를 추가 안됨 수정만 됨
//UECPPSTUDY_API
//editor랑 서로 호환되기 위해서 사용한다

//uint8 >> 8 비트의 부호 정수형
//float 32비트 double 64비트로 지원함
//TArray  vector랑 유사한 방식
//Num():  배열 컨테이너에 현재 몇개의 요소가 저장되어있는지 반환 length와 동일한 기능
//인덱스 기능 제공
//add : 배열의 끝에 요소를 추가함
//remove : 매개변수로 넘긴 인스턴스 모두 제거, 인덱스를 통해서 제거도 가능
//범위기반 for문도 가능하다

//TSubclassOf<>
//일치하는 클래스 객체를 저장한다 안정성을 위해서 사용함

//TEnumAsByte
//안전한 방식으로 열거형 값을 바이트로 저장하는 템플릿입니다.

//람다 모던 c++에서 안씀

UCLASS()
class UECPPSTUDY_API ACPP_Player : public ACharacter,public IIRifle
{
	//GENERATED_BODY 란?
	//언리얼 에서는 어떤 클래스든지 구조체든지 생성자와 소멸자가 필요하다 그것을 대신 만들어 주는 것이 GENERATED_BODY
	GENERATED_BODY()
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

	class ACPP_Rifle* Rifle;

	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
		float ZoomSpeed = 1000;
	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
		FVector2D ZoomRange = FVector2D(0, 500);

public:
	ACPP_Player();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	void OnMoveForward(float AxisValue);
	void OnMoveRight(float AxisValue);
	void OnHorizontalLook(float AxisValue);
	void OnVerticalLook(float AxisValue);
	void OnZoom(float AxisValue);

	void OnRun();
	void OffRun();

	void OnRifle_Equip();

	void OnAim();
	void OffAim();

	void OnFire();
	void OffFire();

	void OnAutoFire();

	// IIRifle을(를) 통해 상속됨
	virtual void Begin_Equip_Rifle() override;
	virtual void End_Equip_Rifle() override;
	virtual void Begin_UnEquip_Rifle() override;
	virtual void End_UnEquip_Rifle() override;
	virtual bool Get_Equip_Rifle() override;
	virtual bool Get_Aim_Rifle() override;
};
