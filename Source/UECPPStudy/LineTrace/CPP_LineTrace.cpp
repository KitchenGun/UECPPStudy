#include "LineTrace/CPP_LineTrace.h"
#include "Components/TextRenderComponent.h"
#include "DrawDebugHelpers.h"
#include "Global.h"

ACPP_LineTrace::ACPP_LineTrace()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Root);

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->Text = FText::FromString(GetName().Replace(L"Defalut_", L""));
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
}

void ACPP_LineTrace::BeginPlay()
{
	Super::BeginPlay();
	
	FVector start = GetActorLocation();

	UKismetSystemLibrary::LineTraceSingleByProfile
	(
		GetWorld(),

		);
}

void ACPP_LineTrace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

