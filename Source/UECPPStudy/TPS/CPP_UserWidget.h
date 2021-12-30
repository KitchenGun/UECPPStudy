#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPP_UserWidget.generated.h"

UCLASS()
class UECPPSTUDY_API UCPP_UserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)//cpp에서 정의 불가능 bp에서만 정의해야함
		void On();
	UFUNCTION(BlueprintImplementableEvent)
		void Off();
};
