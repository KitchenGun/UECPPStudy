#include "Collision/CPP_MultiTrigger.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "../../UECPPStudy/Utilities/CHelpers.h"
#include "../../UECPPStudy/Utilities/CLog.h"

ACPP_MultiTrigger::ACPP_MultiTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Root);
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Root);

	Box->SetRelativeScale3D(FVector(3));//�θ�� ������� ������ Ű���
	Box->bHiddenInGame = false;
	Box->SetCollisionProfileName("CPP_Trigger");//�ݸ��� �������� ����

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->Text = FText::FromString(GetName().Replace(L"Defalut_", L""));
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;

}

void ACPP_MultiTrigger::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this, &ACPP_MultiTrigger::OnBeginOverlap);
	//Box->OnComponentEndOverlap.AddDynamic(this, &ACPP_MultiTrigger::OnEndOverlap);
}

void ACPP_MultiTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_MultiTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OnMultiLightBeginOverlap.IsBound())
	{
		int32 index = UKismetMathLibrary::RandomIntegerInRange(0, 2);
		FLinearColor color;
		color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
		color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
		color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
		color.A = 1.0f;

		OnMultiLightBeginOverlap.Broadcast(index, color);
		//aactor box mesh [3]  mesh�� ���׸��� ���� ��ü
		//aactor sportlight point light [3] light�� ���� ��ü

		//binding addufuction (class , �Լ��̸�) �� ����ؼ� �ذ��ϸ��
	}
}

