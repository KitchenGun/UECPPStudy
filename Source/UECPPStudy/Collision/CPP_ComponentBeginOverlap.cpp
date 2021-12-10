#include "CPP_ComponentBeginOverlap.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/PointLightComponent.h"
#include "../../UECPPStudy/Utilities/CHelpers.h"

ACPP_ComponentBeginOverlap::ACPP_ComponentBeginOverlap()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Root);
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Root);
	CHelpers::CreateComponent<UPointLightComponent>(this, &PointLight, "PointLight", Root);
	
	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->Text = FText::FromString(GetName().Replace(L"Defalut_", L""));
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	PointLight->SetLightColor(FLinearColor::Red);
}

void ACPP_ComponentBeginOverlap::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &ACPP_ComponentBeginOverlap::OnBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &ACPP_ComponentBeginOverlap::OnEndOverlap);
}

void ACPP_ComponentBeginOverlap::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PointLight->SetVisibility(true);
}

void ACPP_ComponentBeginOverlap::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PointLight->SetVisibility(false);
}


