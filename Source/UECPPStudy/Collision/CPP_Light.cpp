#include "Collision/CPP_Light.h"
#include "CPP_Trigger.h"
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
	PointLight->SetVisibility(false);
	PointLight2->SetVisibility(false);

	TArray<AActor*> actors;//포인트 액터 배열
	//월드에 배치된것 중에서 특정 클래스를 가지고 있는 객체들을 반환하는 함수
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACPP_Trigger::StaticClass(), actors);
	ACPP_Trigger* trigger = nullptr;
	if (actors[0])
	{
		trigger = Cast<ACPP_Trigger>(actors[0]);
		trigger->OnBoxLightBeginOverlap.BindUFunction(this,"OnLight");//매개변수와 반환형식을 맞춰줘야한다
		trigger->OnBoxLightEndOverlap.BindUFunction(this, "OffLight");
		trigger->OnBoxLightColorOverlap.BindUFunction(this, "OnRandomLight");
		/*
		OnLight			:Point Light 가 보이도록 설정
		OffLight		:안보이도록 설정
		OnRandomLight	:Point Light2가 랜덤색을 가지도록 설정
		*/
	}
}

void ACPP_Light::OnLight()
{
	PointLight->SetVisibility(true);
	PointLight2->SetVisibility(true);
}

void ACPP_Light::OffLight()
{
	PointLight->SetVisibility(false);
	PointLight2->SetVisibility(false);
}

FString ACPP_Light::OnRandomLight(FLinearColor InColor)
{
	PointLight2->SetVisibility(true);
	PointLight2->SetLightColor(InColor);
	return InColor.ToString();
}


