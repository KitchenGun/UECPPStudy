#include "Parkour/CPP_AnimNotifyParkour.h"
#include "Global.h"
#include "CPP_ParkourComponent.h"


FString UCPP_AnimNotifyParkour::GetNotifyName_Implementation() const
{
	return "Parkour";
}

void UCPP_AnimNotifyParkour::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (!MeshComp)return;

	UCPP_ParkourComponent* parkour = CHelpers::GetComponent<UCPP_ParkourComponent>(MeshComp->GetOwner());
	if (!parkour) return;

	parkour->EndDoParkour();
}
