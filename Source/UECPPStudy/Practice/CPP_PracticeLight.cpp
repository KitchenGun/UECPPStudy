#include "Practice/CPP_PracticeLight.h"
#include "../Collision/CPP_MultiTrigger.h"
#include "../Utilities/CHelpers.h"
#include "Components/PointLightComponent.h"

ACPP_PracticeLight::ACPP_PracticeLight()
{

	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UPointLightComponent>(this, &PointLight[0], "PointLight0", Root);
	CHelpers::CreateComponent<UPointLightComponent>(this, &PointLight[1], "PointLight1", Root);
	CHelpers::CreateComponent<UPointLightComponent>(this, &PointLight[2], "PointLight2", Root);

	PointLight[0]->SetRelativeLocation(FVector(120 * 0, 0, 0));
	PointLight[1]->SetRelativeLocation(FVector(120 * 1, 0, 0));
	PointLight[2]->SetRelativeLocation(FVector(120 * 2, 0, 0));
}

void ACPP_PracticeLight::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> actors;//포인트 액터 배열
	//월드에 배치된것 중에서 특정 클래스를 가지고 있는 객체들을 반환하는 함수
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACPP_MultiTrigger::StaticClass(), actors);
	ACPP_MultiTrigger* trigger = nullptr;
	if (actors[0])
	{
		trigger = Cast<ACPP_MultiTrigger>(actors[0]);
		trigger->OnMultiLightBeginOverlap.AddUFunction(this, "ChangeColor");
	}
}

void ACPP_PracticeLight::ChangeColor(int index, FLinearColor color)
{
	PointLight[index]->SetLightColor(color);
}

