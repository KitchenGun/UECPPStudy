#include "Practice/CPP_PracticeLight.h"
#include "../Collision/CPP_MultiTrigger.h"
#include "../../UECPPStudy/Utilities/CLog.h"
#include "../../UECPPStudy/Utilities/CHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SpotLightComponent.h"
#include "Components/TextRenderComponent.h"

ACPP_PracticeLight::ACPP_PracticeLight()
{

	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text");
	
	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->Text = FText::FromString(GetName().Replace(L"Defalut_", L""));
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	
	for (int32 i = 0; i < 3; i++)
	{
		FString str;
		str.Append("SportLights");
		str.Append(FString::FromInt(i + 1));
		CHelpers::CreateComponent<USpotLightComponent>(this, &SpotLights[i], FName(str), Root);
		SpotLights[i]->SetRelativeLocation(FVector(0,i*150,0));
		SpotLights[i]->SetRelativeRotation(FRotator(-90, 0, 0));
		SpotLights[i]->Intensity = 1e+5f;
		SpotLights[i]->OuterConeAngle = 25;
	}
}

void ACPP_PracticeLight::BeginPlay()
{
	Super::BeginPlay();
	ACPP_MultiTrigger* trigger = CHelpers::FindActor<ACPP_MultiTrigger>(GetWorld());
	if (trigger)
		trigger->OnMultiLightBeginOverlap.AddUFunction(this, "OnLight");

}

void ACPP_PracticeLight::OnLight(int index, FLinearColor color)
{
	for (int32 i = 0; i < 3; i++)
	{
		SpotLights[i]->SetLightColor(FLinearColor(1, 1, 1));
	}
	SpotLights[index]->SetLightColor(color);
}


