#include "TPS/CPP_Rifle.h"
#include "Global.h"


#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Components/SkeletalMeshComponent.h"



ACPP_Rifle::ACPP_Rifle()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CHelpers::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "Mesh");
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Weapons/Meshes/SK_AR4.SK_AR4'");
	Mesh->SetSkeletalMesh(mesh);

	CHelpers::GetAsset<UAnimMontage>(&GrabMontage, "AnimMontage'/Game/Character/Animations/Montage/Rifle_Grab_Montage.Rifle_Grab_Montage'");
	CHelpers::GetAsset<UAnimMontage>(&UnGrabMontage, "AnimMontage'/Game/Character/Animations/Montage/Rifle_UnGrab_Montage.Rifle_UnGrab_Montage'");
}

void ACPP_Rifle::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	//소켓에 컴포넌트를 붙이는 함수
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);
}

void ACPP_Rifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ACPP_Rifle* ACPP_Rifle::Spawn(UWorld* InWorld, ACharacter* InOwnerCharacter)
{
	FActorSpawnParameters params;
	params.Owner = InOwnerCharacter;
	return InWorld->SpawnActor<ACPP_Rifle>(params);
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


