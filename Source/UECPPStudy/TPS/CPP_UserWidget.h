#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPP_UserWidget.generated.h"

UCLASS()
class UECPPSTUDY_API UCPP_UserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)//cpp���� ���� �Ұ��� bp������ �����ؾ���
		void On();
	UFUNCTION(BlueprintImplementableEvent)
		void Off();
};
