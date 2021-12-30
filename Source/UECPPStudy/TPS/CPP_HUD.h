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
private:
	bool bDraw;
	FLinearColor Color = FLinearColor::White;
public:
	FORCEINLINE void Visible() { bDraw = true; }
	FORCEINLINE void InVisible() { bDraw = false; }

	FORCEINLINE void EnableTarget() { Color = FLinearColor::Red; }
	FORCEINLINE void DisableTarget() { Color = FLinearColor::White; }


};
