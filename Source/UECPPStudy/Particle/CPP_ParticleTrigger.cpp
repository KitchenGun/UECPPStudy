#include "Particle/CPP_ParticleTrigger.h"
#include "CPP_Particle.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "../../UECPPStudy/Utilities/CHelpers.h"
#include "../../UECPPStudy/Utilities/CLog.h"

ACPP_ParticleTrigger::ACPP_ParticleTrigger()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Root);
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Root);

	Box->SetRelativeScale3D(FVector(3));//부모와 상관없이 사이즈 키우기
	Box->bHiddenInGame = false;

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->Text = FText::FromString(GetName().Replace(L"Defalut_", L""));
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
}

void ACPP_ParticleTrigger::BeginPlay()
{
	Super::BeginPlay();

	ACPP_Particle* particle = CHelpers::FindActor<ACPP_Particle>(GetWorld());
	if (particle)
		OnActorBeginOverlap.AddDynamic(particle, &ACPP_Particle::ActorBeginOverlap);
}

