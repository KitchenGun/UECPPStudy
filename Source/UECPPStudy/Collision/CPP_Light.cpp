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

	Box->SetRelativeScale3D(FVector(3));//�θ�� ������� ������ Ű���
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

	TArray<AActor*> actors;//����Ʈ ���� �迭
	//���忡 ��ġ�Ȱ� �߿��� Ư�� Ŭ������ ������ �ִ� ��ü���� ��ȯ�ϴ� �Լ�
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACPP_Trigger::StaticClass(), actors);
	ACPP_Trigger* trigger = nullptr;
	if (actors[0])
	{
		trigger = Cast<ACPP_Trigger>(actors[0]);
		trigger->OnBoxLightBeginOverlap.BindUFunction(this,"OnLight");//�Ű������� ��ȯ������ ��������Ѵ�
		trigger->OnBoxLightEndOverlap.BindUFunction(this, "OffLight");
		trigger->OnBoxLightColorOverlap.BindUFunction(this, "OnRandomLight");
		/*
		OnLight			:Point Light �� ���̵��� ����
		OffLight		:�Ⱥ��̵��� ����
		OnRandomLight	:Point Light2�� �������� �������� ����
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


