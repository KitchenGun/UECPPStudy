#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CPP_AnimNotifyParkour.generated.h"

UCLASS()
class UECPPSTUDY_API UCPP_AnimNotifyParkour : public UAnimNotify
{
	GENERATED_BODY()
public:

	FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};
