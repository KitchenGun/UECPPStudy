#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPS/IRifle.h"
#include "CPP_Player.generated.h"//�ڵ�->reflection�����Ϳ� �߰��ϰ� generated.h�� �����Ϳ��� ���߱� ���� ����մϴ� 

//reflection system
//cpp�� ���� ������ editor���� �ľ��ϱ� ���ؼ� ������
//uclass �� uproperty,ustruct �� ������ editor���� �ν��� ���� ����

//construction script  = ������
//���� 
//�����ڴ� ��ü�� ������Ʈ�� �߰� ��Ű�� ������ ����������
//construction script�� ������Ʈ�� �߰� �ȵ� ������ ��
//UECPPSTUDY_API
//editor�� ���� ȣȯ�Ǳ� ���ؼ� ����Ѵ�

//uint8 >> 8 ��Ʈ�� ��ȣ ������
//float 32��Ʈ double 64��Ʈ�� ������
//TArray  vector�� ������ ���
//Num():  �迭 �����̳ʿ� ���� ��� ��Ұ� ����Ǿ��ִ��� ��ȯ length�� ������ ���
//�ε��� ��� ����
//add : �迭�� ���� ��Ҹ� �߰���
//remove : �Ű������� �ѱ� �ν��Ͻ� ��� ����, �ε����� ���ؼ� ���ŵ� ����
//������� for���� �����ϴ�

//TSubclassOf<>
//��ġ�ϴ� Ŭ���� ��ü�� �����Ѵ� �������� ���ؼ� �����

//TEnumAsByte
//������ ������� ������ ���� ����Ʈ�� �����ϴ� ���ø��Դϴ�.

//���� ��� c++���� �Ⱦ�

UCLASS()
class UECPPSTUDY_API ACPP_Player : public ACharacter,public IIRifle
{
	//GENERATED_BODY ��?
	//�𸮾� ������ � Ŭ�������� ����ü���� �����ڿ� �Ҹ��ڰ� �ʿ��ϴ� �װ��� ��� ����� �ִ� ���� GENERATED_BODY
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

	// IIRifle��(��) ���� ��ӵ�
	virtual void Begin_Equip_Rifle() override;
	virtual void End_Equip_Rifle() override;
	virtual void Begin_UnEquip_Rifle() override;
	virtual void End_UnEquip_Rifle() override;
	virtual bool Get_Equip_Rifle() override;
	virtual bool Get_Aim_Rifle() override;
};
