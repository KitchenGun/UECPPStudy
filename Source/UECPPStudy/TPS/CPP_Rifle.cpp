#include "TPS/CPP_Rifle.h"
#include "Global.h"


#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"



ACPP_Rifle::ACPP_Rifle()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CHelpers::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "Mesh");
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Weapons/Meshes/SK_AR4.SK_AR4'");
	Mesh->SetSkeletalMesh(mesh);

	CHelpers::GetAsset<UAnimMontage>(&GrabMontage, "AnimMontage'/Game/Character/Animations/Montage/Rifle_Grab_Montage.Rifle_Grab_Montage'");
	CHelpers::GetAsset<UAnimMontage>(&UnGrabMontage, "AnimMontage'/Game/Character/Animations/Montage/Rifle_UnGrab_Montage.Rifle_UnGrab_Montage'");
	CHelpers::GetAsset<UCurveFloat>(&Curve, "CurveFloat'/Game/FStructs/Curve_Aim.Curve_Aim'");
}

void ACPP_Rifle::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	//���Ͽ� ������Ʈ�� ���̴� �Լ�
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);

	OnTimelineFloat.BindUFunction(this,"Aiming");//�Լ��� ���ε��ؼ� ���� �����Ѵ�.
	Timeline.AddInterpFloat(Curve, OnTimelineFloat);
	Timeline.SetPlayRate(200);
}

void ACPP_Rifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timeline.TickTimeline(DeltaTime);
}

ACPP_Rifle* ACPP_Rifle::Spawn(UWorld* InWorld, ACharacter* InOwnerCharacter)
{
	FActorSpawnParameters params;
	params.Owner = InOwnerCharacter;
	return InWorld->SpawnActor<ACPP_Rifle>(params);
}

void ACPP_Rifle::Firing()
{

}

void ACPP_Rifle::Aiming(float Output)
{
	UCameraComponent* camera = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);
	camera->FieldOfView = Output;
}

void ACPP_Rifle::Equip()
{
	if (bEquipping)
		return;
	bEquipping = true;
	if (bEquipped)
	{
		UnEquip();
		return;
	}
	OwnerCharacter->PlayAnimMontage(GrabMontage,2);
}

void ACPP_Rifle::Begin_Equip()
{
	bEquipped = true;

	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),HandSocket );
}

void ACPP_Rifle::End_Equip()
{
	bEquipping = false;
}

void ACPP_Rifle::UnEquip()
{
	OwnerCharacter->PlayAnimMontage(UnGrabMontage,2);
}

void ACPP_Rifle::Begin_UnEquip()
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);
	bEquipped = false;
}

void ACPP_Rifle::End_UnEquip()
{
	bEquipping = false;
}

void ACPP_Rifle::Begin_Aim()
{
	if (!bEquipped)
		return;
	if (bEquipping)
		return;
	if (!IsAvailableAim())
		return;
	//�ȵǴ� ����Ȯ��
	bAiming = true;
	USpringArmComponent* springArm = CHelpers::GetComponent<USpringArmComponent>(OwnerCharacter);
	//���ӿ� ĳ���� ��������� ����
	OwnerCharacter->bUseControllerRotationYaw = true;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;

	springArm->TargetArmLength = 100;
	springArm->SocketOffset = FVector(0, 30, 10);
	Timeline.PlayFromStart();
}

void ACPP_Rifle::End_Aim()
{
	if (!bAiming)
		return;
	bAiming = false;
	//���ӿ� ĳ���� ������� �ʵ��� ����
	USpringArmComponent* springArm = CHelpers::GetComponent<USpringArmComponent>(OwnerCharacter);
	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;

	springArm->TargetArmLength = 200;
	springArm->SocketOffset = FVector(0, 60, 0);
	Timeline.ReverseFromEnd();
}

void ACPP_Rifle::Begin_Fire()
{
	if (!bEquipped)	return;
	if (bEquipping) return;
	if (!bAiming)	return;
	if (bFiring)	return;
	bFiring = true;

}

void ACPP_Rifle::End_Fire()
{
	bFiring = false;
}

bool ACPP_Rifle::IsAvailableAim()
{
	USpringArmComponent* springArm = CHelpers::GetComponent<USpringArmComponent>(OwnerCharacter); 
	UCameraComponent* camera = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);
	APlayerController* controller = OwnerCharacter->GetController<APlayerController>();
		//Cast<USpringArmComponent>(OwnerCharacter->GetComponentByClass(USpringArmComponent::StaticClass()));//T������ ������ �ִ� ��ü�� ��ȯ

	return springArm&&camera&&controller;
}


