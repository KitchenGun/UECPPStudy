#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UECPPStudyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UECPPSTUDY_API AUECPPStudyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
private:
	TSubclassOf<APawn> player;
public:
	AUECPPStudyGameModeBase();
};
