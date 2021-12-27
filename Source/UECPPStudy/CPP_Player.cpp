#include "CPP_Player.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TPS/CPP_Rifle.h"

ACPP_Player::ACPP_Player()
{
	PrimaryActorTick.bCanEverTick = true;
	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetCapsuleComponent());
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 400;
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'");
	GetMesh()->SetSkeletalMesh(mesh);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	TSubclassOf<UAnimInstance> animInstance;
	CHelpers::GetClass<UAnimInstance>(&animInstance, "AnimBlueprint'/Game/BP/Player/ABP_Player.ABP_Player_C'");
	GetMesh()->SetAnimInstanceClass(animInstance);

	SpringArm->SetRelativeLocation(FVector(0, 0, 60));
	SpringArm->TargetArmLength = 200;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SocketOffset = FVector(0, 60, 0);
	
}

void ACPP_Player::BeginPlay()
{
	Super::BeginPlay();
	Rifle = ACPP_Rifle::Spawn(GetWorld(), this);
}

void ACPP_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward"	, this,&ACPP_Player::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight"		, this, &ACPP_Player::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook"	, this, &ACPP_Player::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook"	, this, &ACPP_Player::OnVerticalLook);
	PlayerInputComponent->BindAxis("Zoom"			, this, &ACPP_Player::OnZoom);

	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &ACPP_Player::OnRun);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &ACPP_Player::OffRun);

	PlayerInputComponent->BindAction("Rifle", EInputEvent::IE_Pressed, this, &ACPP_Player::OnRifle_Equip);

	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Pressed, this, &ACPP_Player::OnAim);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Released, this, &ACPP_Player::OffAim);

	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ACPP_Player::OnFire);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, this, &ACPP_Player::OffFire);

	PlayerInputComponent->BindAction("AutoFire", EInputEvent::IE_Pressed, this, &ACPP_Player::OnAutoFire);
}

void ACPP_Player::OnMoveForward(float AxisValue)
{
	FRotator rotator = FRotator(0, GetController()->GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal();//.Normalize/반환값이 bool 이라서 사용하지 않음

	AddMovementInput(direction, AxisValue);
}

void ACPP_Player::OnMoveRight(float AxisValue)
{
	FRotator rotator = FRotator(0, GetController()->GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal();//.Normalize/반환값이 bool 이라서 사용하지 않음

	AddMovementInput(direction, AxisValue);
}

void ACPP_Player::OnHorizontalLook(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void ACPP_Player::OnVerticalLook(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void ACPP_Player::OnZoom(float AxisValue)
{
	SpringArm->TargetArmLength += (ZoomSpeed * AxisValue * GetWorld()->GetDeltaSeconds());
	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength, ZoomRange.X, ZoomRange.Y);
}

void ACPP_Player::OnRun()
{
	GetCharacterMovement()->MaxWalkSpeed = 600;
}

void ACPP_Player::OffRun()
{
	GetCharacterMovement()->MaxWalkSpeed = 400;
}

void ACPP_Player::OnRifle_Equip()
{
	Rifle->Equip();
}

void ACPP_Player::OnAim()
{
	Rifle->Begin_Aim();
}

void ACPP_Player::OffAim()
{
	Rifle->End_Aim();
}

void ACPP_Player::OnFire()
{
	Rifle->Begin_Fire();
}

void ACPP_Player::OffFire()
{
	Rifle->End_Fire();
}

void ACPP_Player::OnAutoFire()
{
	Rifle->ToggleAutoFire();
}

void ACPP_Player::Begin_Equip_Rifle()
{
	Rifle->Begin_Equip();
}

void ACPP_Player::End_Equip_Rifle()
{
	Rifle->End_Equip();
}

void ACPP_Player::Begin_UnEquip_Rifle()
{
	Rifle->Begin_UnEquip();
}

void ACPP_Player::End_UnEquip_Rifle()
{
	Rifle->End_UnEquip();
}

bool ACPP_Player::Get_Equip_Rifle()
{
	return Rifle->GetEquipped();
}

bool ACPP_Player::Get_Aim_Rifle()
{
	return Rifle->GetAiming();
}


