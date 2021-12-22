#include "TPS/CPP_AnimNotify.h"
#include "Global.h"
#include "IRifle.h"

FString UCPP_AnimNotify::GetNotifyName_Implementation() const
{
	return "Equip";
}


void UCPP_AnimNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if (!MeshComp) return;

	IIRifle* rifle = Cast<IIRifle>(MeshComp->GetOwner());
	if (rifle == nullptr)	return;

	if (bUnequip)
	{
		rifle->Begin_UnEquip_Rifle();
		return;
	}

	rifle->Begin_Equip_Rifle();
}

void UCPP_AnimNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (!MeshComp) return;

	IIRifle* rifle = Cast<IIRifle>(MeshComp->GetOwner());
	if (rifle == nullptr)	return;

	if (bUnequip)
	{
		rifle->End_UnEquip_Rifle();
	}
	rifle->End_Equip_Rifle();
}
