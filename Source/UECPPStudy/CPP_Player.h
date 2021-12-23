#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPS/IRifle.h"
#include "CPP_Player.generated.h"


UCLASS()
class UECPPSTUDY_API ACPP_Player : public ACharacter,public IIRifle
{
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

	// IIRifle을(를) 통해 상속됨
	virtual void Begin_Equip_Rifle() override;
	virtual void End_Equip_Rifle() override;
	virtual void Begin_UnEquip_Rifle() override;
	virtual void End_UnEquip_Rifle() override;
	virtual bool Get_Equip_Rifle() override;
	virtual bool Get_Aim_Rifle() override;
};
