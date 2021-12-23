// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_AnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TPS/IRifle.h"

void UCPP_AnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
}

void UCPP_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (!OwnerCharacter)
		return;
	Speed = OwnerCharacter->GetVelocity().Size2D();
	Direction = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetControlRotation());
	IIRifle* rifle = Cast<IIRifle>(OwnerCharacter);

	if (rifle != nullptr)
	{
		bEquipped = rifle->Get_Equip_Rifle();
		bAiming = rifle->Get_Aim_Rifle();
	}

}
