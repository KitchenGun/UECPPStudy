#include "Collision/CPP_Trigger.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "../../UECPPStudy/Utilities/CHelpers.h"
#include "../../UECPPStudy/Utilities/CLog.h"

ACPP_Trigger::ACPP_Trigger()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Root);
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Root);

	Box->SetRelativeScale3D(FVector(3));//부모와 상관없이 사이즈 키우기
	Box->bHiddenInGame = false;
	Box->SetCollisionProfileName("CPP_Trigger");//콜리전 프로파일 설정

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->Text = FText::FromString(GetName().Replace(L"Defalut_", L""));
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
}

void ACPP_Trigger::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this, &ACPP_Trigger::OnBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &ACPP_Trigger::OnEndOverlap);
}


void ACPP_Trigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OnBoxLightBeginOverlap.IsBound())//현재 설정한 대리자에 어떤 함수가 바인딩이 되어있다면 true 안되있으면 false를 반환한다
	{
		OnBoxLightBeginOverlap.Execute();
	}
	if (OnBoxLightColorOverlap.IsBound())//현재 설정한 대리자에 어떤 함수가 바인딩이 되어있다면 true 안되있으면 false를 반환한다
	{
		FLinearColor color;
		color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
		color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
		color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
		color.A = 1.0f;

		FString str = OnBoxLightColorOverlap.Execute(color);
		CLog::Log("Color : " + str);
	}
}

void ACPP_Trigger::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OnBoxLightEndOverlap.IsBound())//현재 설정한 대리자에 어떤 함수가 바인딩이 되어있다면 true 안되있으면 false를 반환한다
	{
		OnBoxLightEndOverlap.Execute();
	}
}


