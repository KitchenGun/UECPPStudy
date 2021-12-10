#include "Collision/CPP_Light.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/PointLightComponent.h"
#include "../../UECPPStudy/Utilities/CHelpers.h"

ACPP_Light::ACPP_Light()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Root);
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Root);
	CHelpers::CreateComponent<UPointLightComponent>(this, &PointLight, "PointLight", Root);
	CHelpers::CreateComponent<UPointLightComponent>(this, &PointLight2, "PointLight2", Root);

	Box->SetRelativeScale3D(FVector(3));//부모와 상관없이 사이즈 키우기
	Box->bHiddenInGame = false;

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->Text = FText::FromString(GetName().Replace(L"Defalut_", L""));
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	
	PointLight->SetLightColor(FLinearColor::Red);
	PointLight->Intensity = 1e+5f;
	PointLight->AttenuationRadius = 200;

	PointLight2->SetRelativeLocation(FVector(200, 0, 0));
	PointLight2->SetLightColor(FLinearColor::Blue);
	PointLight2->Intensity = 1e+5f;
	PointLight2->AttenuationRadius = 200;
}

void ACPP_Light::BeginPlay()
{
	Super::BeginPlay();
	PointLight->SetVisibility(true);
}


