#include "TPS/CPP_HUD.h"
#include "Global.h"
#include "Engine/Canvas.h"
//hud�� widget ����
/*
hud�� ��ȣ�ۿ��� �ȵǴ� UI
widget�� ��ȣ�ۿ��� �ϴ� UI
*/
ACPP_HUD::ACPP_HUD()
{
	CHelpers::GetAsset<UTexture2D>(&Texture, "Texture2D'/Game/Textures/T_Dot.T_Dot'");
}

void ACPP_HUD::DrawHUD()
{
	Super::DrawHUD();
	if (!bDraw)	return;

	FVector2D center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	FVector2D size(Texture->GetSizeX()*0.5f, Texture->GetSizeY() * 0.5f);
	FVector2D position = center - size;

	FCanvasTileItem item(position,Texture->Resource,Color);

	Canvas->DrawItem(item);


}