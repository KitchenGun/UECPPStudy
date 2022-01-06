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
#include "TPS/CPP_UserWidget.h"
#include "Parkour/CPP_ParkourComponent.h"

ACPP_Player::ACPP_Player()
{
	PrimaryActorTick.bCanEverTick = true;
	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetCapsuleComponent());
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);
	CHelpers::CreateActorComponent<UCPP_ParkourComponent>(this, &Parkour, "Parkour");

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
	

	CHelpers::GetClass<UCPP_UserWidget>(&AutoFireClass, "WidgetBlueprint'/Game/BP/TPS/BP_AutoFire.BP_AutoFire_C'");

	CHelpers::CreateComponent<USceneComponent>(this, &ArrowGroup, "ArrowGroup", GetCapsuleComponent());
	for (int32 i = 0; i < (int32)EParkourArrowType::Max; i++)
	{
		FName name = FName(*CHelpers::GetStringFromEnum("EParkourArrowType", i));
		CHelpers::CreateComponent<UArrowComponent>(this, &Arrows[i], name, ArrowGroup);

		switch ((EParkourArrowType)i)
		{
		case EParkourArrowType::Center://중심
			Arrows[i]->ArrowColor = FColor::Red;
			break;
		case EParkourArrowType::Ceil://머리
			Arrows[i]->ArrowColor = FColor::Green;
			Arrows[i]->SetRelativeLocation(FVector(0, 0, 100));
			break;
		case EParkourArrowType::Floor://바닥
			Arrows[i]->ArrowColor = FColor::Green;
			Arrows[i]->SetRelativeLocation(FVector(0, 0, -80));
			break;
		case EParkourArrowType::Left://왼쪽
			Arrows[i]->ArrowColor = FColor::Magenta;
			Arrows[i]->SetRelativeLocation(FVector(0, -30, 0));
			break;
		case EParkourArrowType::Right://오른쪽
			Arrows[i]->ArrowColor = FColor::Magenta;
			Arrows[i]->SetRelativeLocation(FVector(0, 30, 0));
			break;
		case EParkourArrowType::Land://? 어디에 사용하는지 모르겠음
			Arrows[i]->ArrowColor = FColor::Yellow;
			Arrows[i]->SetRelativeLocation(FVector(200, 0, 100));
			Arrows[i]->SetRelativeRotation(FRotator(-90, 0, 0));
			break;
		default:
			break;
		}
	}
}

void ACPP_Player::BeginPlay()
{
	Super::BeginPlay();
	Rifle = ACPP_Rifle::Spawn(GetWorld(), this);
	AutoFire = CreateWidget<UCPP_UserWidget, APlayerController>(GetController<APlayerController>(), AutoFireClass);
	AutoFire->AddToViewport();

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

	PlayerInputComponent->BindAction("Parkour", EInputEvent::IE_Pressed, this, &ACPP_Player::OnParkour);
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
	Rifle->GetAutoFire()? AutoFire->On(): AutoFire->Off();
}

void ACPP_Player::OnParkour()
{
	Parkour->DoParkour();
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


