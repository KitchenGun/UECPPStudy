#include "TPS/CPP_Rifle.h"
#include "CPP_Bullet.h"
#include "CPP_HUD.h"
#include "Global.h"

#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/DecalComponent.h"

#include "Animation/AnimMontage.h"
#include "Camera/CameraComponent.h"

#include "Sound/SoundCue.h"
#include "Particles/ParticleSystemComponent.h"
#include "Materials/MaterialInstanceConstant.h"



ACPP_Rifle::ACPP_Rifle()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CHelpers::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "Mesh");
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Weapons/Meshes/SK_AR4.SK_AR4'");
	Mesh->SetSkeletalMesh(mesh);

	CHelpers::GetAsset<UAnimMontage>(&GrabMontage, "AnimMontage'/Game/Character/Montages/Rifle_Grab_Montage.Rifle_Grab_Montage'");
	CHelpers::GetAsset<UAnimMontage>(&UnGrabMontage, "AnimMontage'/Game/Character/Montages/Rifle_UnGrab_Montage.Rifle_UnGrab_Montage'");
	CHelpers::GetAsset<UCurveFloat>(&Curve, "CurveFloat'/Game/FStructs/Curve_Aim.Curve_Aim'");
	CHelpers::GetClass<UMatineeCameraShake>(&CameraShakeClass, "Blueprint'/Game/BP/TPS/BP_CameraShake.BP_CameraShake_C'");
	CHelpers::GetAsset<USoundCue>(&MuzzleSoundCue, "SoundCue'/Game/Sounds/S_RifleShoot_Cue.S_RifleShoot_Cue'");
	CHelpers::GetAsset<UParticleSystem>(&FlashParticle, "ParticleSystem'/Game/Particles_Rifle/Particles/VFX_Muzzleflash.VFX_Muzzleflash'");
	CHelpers::GetAsset<UParticleSystem>(&EjectParticle, "ParticleSystem'/Game/Particles_Rifle/Particles/VFX_Eject_bullet.VFX_Eject_bullet'");
	CHelpers::GetClass<ACPP_Bullet>(&BulletClass, "Blueprint'/Game/BP/TPS/BP_Bullet.BP_Bullet_C'");
	CHelpers::GetAsset<UParticleSystem>(&ImpactParticle, "ParticleSystem'/Game/Particles_Rifle/Particles/VFX_Impact_Default.VFX_Impact_Default'");
	CHelpers::GetAsset<UMaterialInstanceConstant>(&ImpactDecal, "MaterialInstanceConstant'/Game/Materials/M_Decal_Inst.M_Decal_Inst'");
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

	Delay = 0;
}

void ACPP_Rifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timeline.TickTimeline(DeltaTime);

	Delay -= DeltaTime;

	if(bAiming)//Hud �� ���ؽ� ���� ����
	{
		//ī�޶� ������Ʈ����
		UCameraComponent* camera = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);
		FTransform transform = camera->GetComponentToWorld();
		FVector direction = camera->GetForwardVector();
		FVector start = transform.GetLocation() + direction;
		FVector end = transform.GetLocation() + direction * AimDistance;

		ACPP_HUD* hub = OwnerCharacter->GetController<APlayerController>()->GetHUD<ACPP_HUD>();

		//linetrace
		TArray<AActor*> ignoreActors;//�ڱ� �ڽ��浹 �����ϱ� ���ؼ�
		ignoreActors.Add(OwnerCharacter);

		FHitResult hitResult;

		UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, end, ETraceTypeQuery::TraceTypeQuery3, false, ignoreActors, EDrawDebugTrace::None, hitResult, true);
		UStaticMeshComponent* mesh = Cast<UStaticMeshComponent>(hitResult.GetActor()->GetRootComponent());

		if (hitResult.bBlockingHit)
		{
			hub->EnableTarget();
		}
		else
		{
			hub->DisableTarget();
		}
	}

}

ACPP_Rifle* ACPP_Rifle::Spawn(UWorld* InWorld, ACharacter* InOwnerCharacter)
{
	FActorSpawnParameters params;
	params.Owner = InOwnerCharacter;
	return InWorld->SpawnActor<ACPP_Rifle>(params);
}

void ACPP_Rifle::Firing()
{
	FVector direction,start,end;

	if (IsAvailableAim())
	{
		//ī�޶� ������Ʈ����
		UCameraComponent* camera = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);
		FTransform transform = camera->GetComponentToWorld();
		direction = camera->GetForwardVector();
		start = transform.GetLocation() + direction;
		end = transform.GetLocation() + direction * AimDistance;
		//�ݵ�
		APlayerController* controller = OwnerCharacter->GetController<APlayerController>();
		if (CameraShakeClass)	controller->PlayerCameraManager->StartCameraShake(CameraShakeClass);

	}
	
	FVector muzzleLocation = Mesh->GetSocketLocation("MuzzleFlash");

	//sound
	{
		if (MuzzleSoundCue)
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), MuzzleSoundCue, muzzleLocation);
	}
	//particle
	{
		if (FlashParticle)
			UGameplayStatics::SpawnEmitterAttached(FlashParticle, Mesh, "MuzzleFlash",FVector::ZeroVector,FRotator::ZeroRotator,EAttachLocation::KeepRelativeOffset);
		if (EjectParticle)
			UGameplayStatics::SpawnEmitterAttached(EjectParticle, Mesh, "EjectBullet", FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset);
	}
	//bullet
	{
		if (BulletClass)
		{
			FVector spawnLocation = muzzleLocation + direction * 100;
			ACPP_Bullet* bullet = GetWorld()->SpawnActor<ACPP_Bullet>(BulletClass, spawnLocation, direction.Rotation());
			bullet->Shot(direction);
		}
	}

	//�ݵ�
	{
		PitchAngle -= 0.25 * GetWorld()->DeltaTimeSeconds;
		OwnerCharacter->AddControllerPitchInput(PitchAngle);
	}

	//linetrace
	TArray<AActor*> ignoreActors;//�ڱ� �ڽ��浹 �����ϱ� ���ؼ�
	ignoreActors.Add(OwnerCharacter);

	FHitResult hitResult;

	UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, end, ETraceTypeQuery::TraceTypeQuery1, false, ignoreActors, EDrawDebugTrace::None, hitResult, true);
	//��Į
	if (hitResult.bBlockingHit)
	{
		FRotator rotator = hitResult.ImpactNormal.Rotation();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, hitResult.Location, rotator);
		//�ǰ� ���� ǥ��
		UDecalComponent* decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), ImpactDecal, FVector(5), hitResult.Location, rotator, 10);
		decal->SetFadeScreenSize(0);
		//�浹 ó���ϱ� ���ؼ� �浹 ��ü�� �Ž��� ������
		UStaticMeshComponent* mesh = Cast<UStaticMeshComponent>(hitResult.GetActor()->GetRootComponent());
		if (mesh && mesh->BodyInstance.bSimulatePhysics)//mesh�� �����ϴ����� ������ �����ִ��� Ȯ��
		{
			direction = hitResult.GetActor()->GetActorLocation() - OwnerCharacter->GetActorLocation();//����
			direction.Normalize();//����ȭ
			mesh->AddImpulseAtLocation(direction * 300, OwnerCharacter->GetActorLocation());//�ش� ��ġ�� ����ȿ�� ��
		}
	}

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
	//aim ǥ�� Ű��
	OwnerCharacter->GetController<APlayerController>()->GetHUD<ACPP_HUD>()->Visible();
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
	//aim ǥ�� ����
	OwnerCharacter->GetController<APlayerController>()->GetHUD<ACPP_HUD>()->InVisible();
}

void ACPP_Rifle::Begin_Fire()
{
	if (!bEquipped)	return;
	if (bEquipping) return;
	if (!bAiming)	return;
	if (bFiring)	return;
	if (Delay > 0)
	{
		CLog::Log("Over rate");
		return;
	}
	bFiring = true;
	
	if (bAutoFire)
	{
		//UKismetSystemLibrary::K2_SetTimer(this, "Firing", 0.085f, true);//ufunction�� ���ε��� �ȴ�
		GetWorld()->GetTimerManager().SetTimer(AutoFireHandle, this, &ACPP_Rifle::Firing, 0.085f, true, 0);
		return;
	}
	Delay = 0.085f;
	Firing();
}

void ACPP_Rifle::End_Fire()
{
	bFiring = false;
	if (bAutoFire)
		GetWorld()->GetTimerManager().ClearTimer(AutoFireHandle);
		//UKismetSystemLibrary::K2_ClearTimer(this, "Firing");
}

void ACPP_Rifle::ToggleAutoFire()
{
	if (!bFiring)
		bAutoFire = !bAutoFire;
}

bool ACPP_Rifle::IsAvailableAim()
{
	USpringArmComponent* springArm = CHelpers::GetComponent<USpringArmComponent>(OwnerCharacter); 
	UCameraComponent* camera = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);
	APlayerController* controller = OwnerCharacter->GetController<APlayerController>();
		//Cast<USpringArmComponent>(OwnerCharacter->GetComponentByClass(USpringArmComponent::StaticClass()));//T������ ������ �ִ� ��ü�� ��ȯ

	return springArm&&camera&&controller;
}


