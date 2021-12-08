#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Log.generated.h"

UCLASS()
class UECPPSTUDY_API ACPP_Log : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPP_Log();

protected:
	virtual void BeginPlay() override;

};
