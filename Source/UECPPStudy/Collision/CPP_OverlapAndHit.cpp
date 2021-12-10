#include "CPP_OverlapAndHit.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/PointLightComponent.h"
#include "../../UECPPStudy/Utilities/CHelpers.h"
#include "../../UECPPStudy/Utilities/CLog.h"


ACPP_OverlapAndHit::ACPP_OverlapAndHit()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Root);
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Root);
	CHelpers::CreateComponent<UPointLightComponent>(this, &PointLight, "PointLight", Root);

	Box->SetRelativeScale3D(FVector(3));//부모와 상관없이 사이즈 키우기
	Box->bHiddenInGame = false;
	Box->SetCollisionProfileName("CPP_OverlapAndHit");//콜리전 프로파일 설정

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->Text = FText::FromString(GetName().Replace(L"Defalut_", L""));
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	PointLight->SetLightColor(FLinearColor::Red);
}

void ACPP_OverlapAndHit::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &ACPP_OverlapAndHit::OnBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &ACPP_OverlapAndHit::OnEndOverlap);
	Box->OnComponentHit.AddDynamic(this, &ACPP_OverlapAndHit::OnHit);
}

void ACPP_OverlapAndHit::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CLog::Log("In : " + OtherActor->GetName());
}

void ACPP_OverlapAndHit::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CLog::Log("Out : " + OtherActor->GetName());
}

void ACPP_OverlapAndHit::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FString str;
	str.Append("Hit : " + OtherActor->GetName());
	str.Append(" / ");
	str.Append(FString::FromInt(++HitCount));

	CLog::Log(str);
}
