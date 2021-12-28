#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CPP_HUD.generated.h"

//hud 
/*
	widgetµéÀ» ¶ç¿ì´Â °´Ã¼
*/

UCLASS()
class UECPPSTUDY_API ACPP_HUD : public AHUD
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
		class UTexture2D* Texture;

public:
	ACPP_HUD();

	virtual void DrawHUD() override;

};
